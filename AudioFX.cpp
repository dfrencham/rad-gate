#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

#include "constants.h"
#include "utility.h"
#include "AudioFX.h"

AudioFX::AudioFX() {

  SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
  ss.begin(9600);
  Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
}

AudioFX::~AudioFX() {

}

void AudioFX::start_tone(int hz) {
  tone(PIN_SPEAKER, TONE_DROP_HZ);
}

void AudioFX::stop_tone() {
  noTone(PIN_SPEAKER);
}

void AudioFX::play_sound_samples() {
  if (!ENABLE_VOICE_CADENCE) {
    serial_print("Skipping voice cadence");
    return;
  }

  serial_print("Play Sample1");
  sfx->playTrack(SFX_PREP);
  delay(50);
  while (digitalRead(SFX_ACT) == LOW) {
    // wait for sample to finish
  }
  delay(1750);
  serial_print("Play Sample2");
  sfx->playTrack(SFX_WATCH_GATE);
  delay(50);
  while (digitalRead(SFX_ACT) == LOW) {
    // wait for sample to finish
  }
  serial_print("SFX Done");
}

void AudioFX::play_abort() {
  tone(PIN_SPEAKER, TONE_ABORT_1_HZ, DELAY_ABORT_TONE_1_MS);
  delay(DELAY_ABORT_TONE_1_MS);
  tone(PIN_SPEAKER, TONE_ABORT_2_HZ, DELAY_ABORT_TONE_2_MS);
}
