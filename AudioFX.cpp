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
#include "Volume3.h"

#ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
  bool SFX_ADAFRUIT = 1;
#endif
#ifdef HARDWARE_SOUNDBOARD_JQ6500
  bool SFX_ADAFRUIT = 0;
#endif

Volume vol;

AudioFX::AudioFX(Adafruit_Soundboard *sbref) {
  sfx = sbref;
}

AudioFX::AudioFX(JQ6500_Serial *jref) {
  jfx = jref;
}

void AudioFX::start_tone(int hz) {
  serial_print("Tone");
  vol.tone(PIN_SPEAKER, TONE_DROP_HZ,TONE_VOLUME);
}

void AudioFX::stop_tone() {
  vol.noTone();
}

void AudioFX::play_sound_samples() {
  if (!ENABLE_VOICE_CADENCE) {
    serial_print("Skipping voice cadence");
    return;
  }

  serial_print("Play Sample1");
  play_sample(SFX_PREP);
  delay(1750);
  serial_print("Play Sample2");
  play_sample(SFX_WATCH_GATE);
  serial_print("SFX Done");
}

void AudioFX::play_abort() {
  vol.tone(PIN_SPEAKER, TONE_ABORT_1_HZ, TONE_VOLUME);
  delay(DELAY_ABORT_TONE_1_MS);
  vol.tone(PIN_SPEAKER, TONE_ABORT_2_HZ, TONE_VOLUME);
  delay(DELAY_ABORT_TONE_2_MS);
  vol.noTone();
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
    serial_print("SFX playing on QJ6500 device");
    jfx->playFileByIndexNumber(track);
    delay(50);
    while(jfx->getStatus() != MP3_STATUS_STOPPED)
    {
         // wait for sample to finish
    }
  }
  return;
}

void AudioFX::play_coin_up() {
  int start_vol = 130;
  vol.tone(PIN_SPEAKER,1025,start_vol); // pa
  delay(70);
  int v = start_vol;
  while(v > 0){
    vol.tone(PIN_SPEAKER,2090,v); // ting!
    delay(3);
    v--;
  }
  vol.noTone();
}
