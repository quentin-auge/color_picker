#include "pins.h"
#include "RTTTLPlayer.h"
#include "songs.h"
#include "Button.h"
#include "LedController.h"
#include "leds.h"
#include "BLEManager.h"

Button rButton(BUTTON_R_PIN);
Button gButton(BUTTON_G_PIN);
Button bButton(BUTTON_B_PIN);

LedController rLed;
LedController gLed;
LedController bLed;

Button backButton(BUTTON_BACK_PIN);
RTTTLPlayer player(BUZZER_PIN);

BLEManager bleManager;

void setup() {
  Serial.begin(9600);

  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(BUTTON_R_PIN, INPUT_PULLUP);
  pinMode(BUTTON_G_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);

  pinMode(BUTTON_BACK_PIN, INPUT_PULLUP);

  analogSetAttenuation(ADC_11db);

  bleManager.setup();

  delay(50);
  Serial.println("Connection established!");
}

int song_idx = 0;

bool wasPlaying = false;

int tunedBrightness = MAX_BRIGHTNESS / 2;

int rBleBrightness = -1;  // Deactivated
int gBleBrightness = -1;  // Deactivated
int bBleBrightness = -1;  // Deactivated

bool hasBleRtttl = false;
char bleRtttlBuffer[RTTTL_BUFFER_SIZE];

void loop() {
  int potentiometerValue = 4095 - analogRead(POTENTIOMETER_PIN);

  if (bleManager.hasColorUpdate()) {
    rLed.turnOn(); gLed.turnOn(); bLed.turnOn();
    rBleBrightness = bleManager.getR();
    gBleBrightness = bleManager.getG();
    bBleBrightness = bleManager.getB();
    // Disallow all LEDs to be off at once, or it becomes difficult to reset
    if (rBleBrightness == 0 && gBleBrightness == 0 && bBleBrightness == 0) {
      rBleBrightness = MIN_BRIGHTNESS;
      gBleBrightness = MIN_BRIGHTNESS;
      bBleBrightness = MIN_BRIGHTNESS;
    }
  }

  if (bleManager.hasRtttlUpdate()) {
    const char* rtttl = bleManager.getRtttl();
    strncpy(bleRtttlBuffer, rtttl, sizeof(bleRtttlBuffer) - 1);
    bleRtttlBuffer[sizeof(bleRtttlBuffer) - 1] = '\0';
    hasBleRtttl = true;
    Serial.println("Received RTTTL from BLE");
  }

  if (hasBleRtttl) {
    if (bleRtttlBuffer[0] == '\0') {
      player.stop();
      Serial.println("Stopping playback");
    } else {
      player.stop();
      player.play(bleRtttlBuffer);
      Serial.println("Playing RTTTL from BLE");
    }
    hasBleRtttl = false;
  }

  // Handle back button

  backButton.update();

  if (backButton.isPressed()) {
    wasPlaying = player.isPlaying();
    if (player.isPlaying()) {
      player.stop();
      setRGBFromPitch(0);
    }
  }

  if (backButton.isReleased()) {
    if (player.isStopped() && !wasPlaying) {
      player.play(ALL_SONGS[song_idx]);
    }
  }

  if (backButton.isMultiClick()) {
    song_idx = (song_idx + 1) % NB_SONGS;
    player.play(ALL_SONGS[song_idx]);
  }

  if (player.isPlaying())
  {
    // Handle tempo tuning with potentiometer
    int base = player.getBaseTempo();
    int tempo = map(potentiometerValue, 0, 4095, base / 2, base * 2);
    player.setTempo(tempo);
    player.update();
    setRGBFromPitch(player.getPitch());
  }

  if (!player.isPlaying())
  {
    // Handle RGB LEDs / buttons
    rButton.update();
    gButton.update();
    bButton.update();

    // Turning of all LEDs puts an end to BLE color control.
    // It is not possible to have all LEDs at 0 at once here so there is no mistakenly disabling.
    if ((!rLed.isOn() || rBleBrightness == 0) &&
        (!gLed.isOn() || gBleBrightness == 0) &&
        (!bLed.isOn() || bBleBrightness == 0)) {
      rLed.turnOff(); gLed.turnOff(); bLed.turnOff();
      rBleBrightness = -1; gBleBrightness = -1; bBleBrightness = -1;
    }

    // No LED blinking -> brightness tuning
    if (!rLed.isBlinking() && !gLed.isBlinking() && !bLed.isBlinking()) {
      rLed.brightnessTuningOn();
      gLed.brightnessTuningOn();
      bLed.brightnessTuningOn();
    }

    // Button press -> on/off
    if (rButton.isPressed() && !rLed.isBlinking()) { rLed.toggleOnOff(); }
    if (gButton.isPressed() && !gLed.isBlinking()) { gLed.toggleOnOff(); }
    if (bButton.isPressed() && !bLed.isBlinking()) { bLed.toggleOnOff(); }

    // Multi-click -> blinking on/off
    if (rButton.isMultiClick()) { rLed.turnOn(); rLed.toggleBlinking(); }
    if (gButton.isMultiClick()) { gLed.turnOn(); gLed.toggleBlinking(); }
    if (bButton.isMultiClick()) { bLed.turnOn(); bLed.toggleBlinking(); }

    if (rButton.isMultiClick() || gButton.isMultiClick() || bButton.isMultiClick()) {
      // Entering/exiting blinking -> disable brightness tuning for all LEDs
      rLed.brightnessTuningOff();
      gLed.brightnessTuningOff();
      bLed.brightnessTuningOff();

      // Synchronize blinking clock between LEDs
      unsigned long syncTime = millis();
      rLed.syncBlink(syncTime);
      gLed.syncBlink(syncTime);
      bLed.syncBlink(syncTime);
    }

    // Button press when blinking -> off
    if (rButton.isShortPress() && rLed.isBlinking()) { rLed.blinkingOff(); rLed.turnOff(); }
    if (gButton.isShortPress() && gLed.isBlinking()) { gLed.blinkingOff(); gLed.turnOff(); }
    if (bButton.isShortPress() && bLed.isBlinking()) { bLed.blinkingOff(); bLed.turnOff(); }

    // Update LEDs brightness
    int rBrightness = rLed.update(potentiometerValue, &tunedBrightness, rBleBrightness);
    int gBrightness = gLed.update(potentiometerValue, &tunedBrightness, gBleBrightness);
    int bBrightness = bLed.update(potentiometerValue, &tunedBrightness, bBleBrightness);

    // Light LEDs
    analogWrite(LED_R_PIN, rBrightness);
    analogWrite(LED_G_PIN, gBrightness);
    analogWrite(LED_B_PIN, bBrightness);
  }
}
