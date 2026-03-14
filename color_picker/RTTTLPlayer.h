#pragma once
#include <Arduino.h>

typedef const char* Song;

class RTTTLPlayer {
public:
  RTTTLPlayer(int buzzerPin);

  void play(Song rtttl);
  bool update();
  void stop();
  void pause();
  void resume();

  void setTempo(int tempo);

  bool isPlaying()  const;
  bool isPaused()   const;
  bool isStopped()  const;
  bool isFinished() const;

  int  getPitch()      const;
  int  getBaseTempo()  const;   // tempo parsed from the RTTTL header

private:
  int _buzzerPin;

  // RTTTL source
  Song         _rtttl;
  const char*  _cursor;

  // Defaults parsed from the header
  int _defaultDuration;
  int _defaultOctave;
  int _baseTempo;

  // Current music player state
  bool _active;
  bool _paused;
  bool _finished;
  int _tempo;

  // Current note state
  int           _pitch;
  unsigned long _noteStartMs;
  int           _noteDurationMs;
  bool          _noteToneActive;

  void _parseHeader();
  bool _parseNextNote();
  void _startTone();
  void _advanceNote();

  static const char* _skipToColon(const char* p);
  static int _eatInt(const char*& p, int fallback);
  static int _noteCharToIndex(char c);
};
