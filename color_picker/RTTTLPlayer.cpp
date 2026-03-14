#include "RTTTLPlayer.h"

// Frequencies for C, C#, D, D#, E, F, F#, G, G#, A, A#, B  in octave 0.
// Multiply by 2^octave to get the real frequency.
// We store octave-4 values and shift at parse time.
static const int NOTE_FREQ_O4[] = {
  262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494
};

// Map note-letter index (0-6 = C D E F G A B) → semitone index in the chromatic scale
static const int LETTER_TO_SEMI[] = { 0, 2, 4, 5, 7, 9, 11 };

RTTTLPlayer::RTTTLPlayer(int buzzerPin)
  : _buzzerPin(buzzerPin),
    _rtttl(nullptr),
    _cursor(nullptr),
    _defaultDuration(0),
    _defaultOctave(0),
    _baseTempo(0),
    _tempo(0),
    _pitch(0),
    _noteStartMs(0),
    _noteDurationMs(0),
    _noteToneActive(false),
    _active(false),
    _paused(false),
    _finished(false)
{}

void RTTTLPlayer::play(Song rtttl) {
  noTone(_buzzerPin);

  _rtttl = rtttl;
  _parseHeader();  // sets _cursor, _defaultDuration, _defaultOctave, _baseTempo
  _tempo = _baseTempo;

  _pitch          = 0;
  _noteToneActive = false;
  _active         = true;
  _paused         = false;
  _finished       = false;
}

bool RTTTLPlayer::update() {
  if (!_active || _paused || _finished) return false;

  unsigned long now = millis();

  // Need to start a new note?
  if (!_noteToneActive) {
    if (!_parseNextNote()) {
      noTone(_buzzerPin);
      _active   = false;
      _finished = true;
      return false;
    }
    _startTone();
    _noteStartMs    = now;
    _noteToneActive = true;
  }

  // Has the current note finished?
  if (now - _noteStartMs >= (unsigned long)_noteDurationMs) {
    _advanceNote();
  }

  return true;
}

void RTTTLPlayer::stop() {
  noTone(_buzzerPin);
  _active         = false;
  _paused         = false;
  _finished       = false;
  _noteToneActive = false;
}

void RTTTLPlayer::pause() {
  if (!_active || _paused) return;
  noTone(_buzzerPin);
  _paused         = true;
  _noteToneActive = false;
}

void RTTTLPlayer::resume() {
  if (!_active || !_paused) return;
  _paused      = false;
  _noteStartMs = millis();
}

void RTTTLPlayer::setTempo(int tempo) { _tempo = tempo; }

bool RTTTLPlayer::isPlaying()  const { return _active && !_paused && !_finished; }
bool RTTTLPlayer::isPaused()   const { return _paused; }
bool RTTTLPlayer::isStopped()  const { return !_active; }
bool RTTTLPlayer::isFinished() const { return _finished; }

int  RTTTLPlayer::getPitch()     const { return _pitch; }
int  RTTTLPlayer::getBaseTempo() const { return _baseTempo; }

// ==============
//  RTTTL parser
// ==============

void RTTTLPlayer::_parseHeader() {
  const char* p = _rtttl;

  // 1) Skip name section
  p = _skipToColon(p);

  // 2) Parse defaults:  d=4,o=6,b=120  (any order, any subset)
  _defaultDuration = 4;
  _defaultOctave   = 6;
  _baseTempo       = 63;

  const char* endDefaults = p;
  while (*endDefaults && *endDefaults != ':') ++endDefaults;

  while (p < endDefaults) {
    while (p < endDefaults && (*p == ' ' || *p == ',')) ++p;
    if (p >= endDefaults) break;
    char key = tolower(*p); ++p;
    if (*p == '=') ++p;
    int val = _eatInt(p, 0);
    switch (key) {
      case 'd': _defaultDuration = val; break;
      case 'o': _defaultOctave   = val; break;
      case 'b': _baseTempo       = val; break;
    }
  }

  // 3) Advance past the second ':'
  _cursor = endDefaults;
  if (*_cursor == ':') ++_cursor;
}

// Skip past the next ':' and return a pointer to the char after it.
const char* RTTTLPlayer::_skipToColon(const char* p) {
  while (*p && *p != ':') ++p;
  if (*p == ':') ++p;
  return p;
}

int RTTTLPlayer::_eatInt(const char*& p, int fallback) {
  if (!isdigit(*p)) return fallback;
  int v = 0;
  while (isdigit(*p)) { v = v * 10 + (*p - '0'); ++p; }
  return v;
}

int RTTTLPlayer::_noteCharToIndex(char c) {
  switch (tolower(c)) {
    case 'c': return 0;
    case 'd': return 1;
    case 'e': return 2;
    case 'f': return 3;
    case 'g': return 4;
    case 'a': return 5;
    case 'b': return 6;
    default:  return -1;
  }
}

// Parse the next note from _cursor.  Returns false if end-of-string.
// Sets _pitch and _noteDurationMs.
bool RTTTLPlayer::_parseNextNote() {
  const char* p = _cursor;

  // Skip whitespace / commas
  while (*p == ' ' || *p == ',') ++p;
  if (*p == '\0') return false;

  // 1) Optional duration number
  int dur = _eatInt(p, _defaultDuration);

  // 2) Note letter (or 'p' for pause/rest)
  char noteChar = tolower(*p);
  if (noteChar == '\0') return false;
  ++p;

  bool isRest = (noteChar == 'p');
  int  letterIdx = isRest ? -1 : _noteCharToIndex(noteChar);

  // 3) Optional '#' (sharp)
  bool sharp = false;
  if (*p == '#') { sharp = true; ++p; }

  // 4) Optional '.' (dotted note)
  bool dotted = false;
  if (*p == '.') { dotted = true; ++p; }

  // 5) Optional octave digit
  int octave = _eatInt(p, _defaultOctave);

  // 6) Another chance for '.' after octave (some RTTTL variants)
  if (*p == '.') { dotted = true; ++p; }

  _cursor = p;

  // Compute frequency
  if (isRest || letterIdx < 0) {
    _pitch = 0;
  } else {
    int semi = LETTER_TO_SEMI[letterIdx] + (sharp ? 1 : 0);
    // Compute frequency: start from octave-4 table and shift
    int freq = NOTE_FREQ_O4[semi];
    int shift = octave - 4;
    if (shift > 0) freq <<= shift;
    else if (shift < 0) freq >>= (-shift);
    _pitch = freq;
  }

  // Compute duration in ms
  int wholenote = (60000 * 4) / _tempo;
  _noteDurationMs = wholenote / dur;
  if (dotted) _noteDurationMs = (int)(_noteDurationMs * 1.5f);

  return true;
}

void RTTTLPlayer::_startTone() {
  if (_pitch > 0) {
    tone(_buzzerPin, _pitch, (int)(_noteDurationMs * 0.9f));
  }
}

void RTTTLPlayer::_advanceNote() {
  noTone(_buzzerPin);
  _noteToneActive = false;
}
