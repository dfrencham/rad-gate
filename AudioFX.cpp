/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <SoftwareSerial.h>

#include "Adafruit_Soundboard.h"
#include <JQ6500_Serial.h>

#include "constants.h"
#include "utility.h"
#include "AudioFX.h"

#ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
  bool SFX_ADAFRUIT = 1;
#endif
#ifdef HARDWARE_SOUNDBOARD_JQ6500
  bool SFX_ADAFRUIT = 0;
#endif

AudioFX::AudioFX(Adafruit_Soundboard *sbref) {
  sfx = sbref;
}

AudioFX::AudioFX(JQ6500_Serial *jref) {
  jfx = jref;
}

void AudioFX::start_tone(int hz) {
  serial_print("Tone");
  tone(PIN_SPEAKER, TONE_DROP_HZ);
}

void AudioFX::stop_tone() {
  noTone(PIN_SPEAKER);
}

void AudioFX::play_power_on() {
  tone(PIN_SPEAKER, 1000, 100);
  delay(100);
  tone(PIN_SPEAKER, 1333, 600);
  delay(600);
}

void AudioFX::play_sound_samples() {
  if (!ENABLE_VOICE_CADENCE) {
    serial_print("Skipping voice cadence");
    return;
  }

  serial_print("Play Sample1");
  play_sample(SFX_PREP,2013);
  delay(1750);
  serial_print("Play Sample2");
  play_sample(SFX_WATCH_GATE,2330);
  serial_print("SFX Done");
}

void AudioFX::play_abort() {
  tone(PIN_SPEAKER, TONE_ABORT_1_HZ, DELAY_ABORT_TONE_1_MS);
  delay(DELAY_ABORT_TONE_1_MS);
  tone(PIN_SPEAKER, TONE_ABORT_2_HZ, DELAY_ABORT_TONE_2_MS);
}

void AudioFX::play_sample(uint8_t track) {
  if (SFX_ADAFRUIT) {
    serial_print("SFX playing on Adafruit device");
    sfx->playTrack(track);
    delay(50);
    while (digitalRead(PIN_SFX_ACT) == LOW) {
      // wait for sample to finish
    }
  }
  else
  {
    // NOTE - for some annoying reason, serial transmission
    // from the JQ6500 causes interference while audio is playing.
    // We need to use the method below (passing in playtime) to
    // finish playing when the track finishes. It is a crap way to do
    // it, but for $3 for a JQ6500, I can live with it.
    serial_print("SFX playing on QJ6500 device");
    jfx->playFileByIndexNumber(track);
    delay(50);
    while(jfx->getStatus() == MP3_STATUS_PLAYING)
    {
         // wait for sample to finish
         // debug
         //serial_print_val("SFX Status",jfx->getStatus());
    }
    serial_print("SFX done");
  }
  return;
}

// needed for JQ6500, because cheap crap.
void AudioFX::play_sample(uint8_t track, int playTime) {
  if (SFX_ADAFRUIT) {
    serial_print("SFX playing on Adafruit device");
    sfx->playTrack(track);
    delay(playTime);
  }
  else
  {
    serial_print("SFX playing on QJ6500 device");
    jfx->playFileByIndexNumber(track);
    delay(playTime);
  }
  serial_print("SFX done");
  return;
}
