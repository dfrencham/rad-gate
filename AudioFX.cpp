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
  // serial_print_val("Tone", TONE_DROP_HZ);
  tone(PIN_SPEAKER, TONE_DROP_HZ);
}

void AudioFX::stop_tone() {
  // serial_print("Tone Stop");
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

  serial_print("Play 1.mp3");
  play_sample(SFX_PREP); // try this first. If use below
  // play_sample(SFX_PREP,2013);  // file_number, play_time
  delay(1750);
  serial_print("Play 2.mp3");
  play_sample(SFX_WATCH_GATE);
  //play_sample(SFX_WATCH_GATE,2330); // file_number, play_time
  serial_print("SFX mp3 play Done");
}

void AudioFX::play_abort() {
  serial_print("playing abort tones");
  tone(PIN_SPEAKER, TONE_ABORT_1_HZ, DELAY_ABORT_TONE_1_MS);
  delay(DELAY_ABORT_TONE_1_MS);
  tone(PIN_SPEAKER, TONE_ABORT_2_HZ, DELAY_ABORT_TONE_2_MS);
}

void AudioFX::play_sample(uint8_t track) {
  if (SFX_ADAFRUIT) {
    serial_print("a. SFX playing on Adafruit device");
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
    serial_print("a. SFX playing on JQ6500 device");
    jfx->playFileByIndexNumber(track);
    delay(150);
    byte stat =jfx->getStatus();  //0x00 , 0x01, 0x02 Stopped/Playing/Paused
    serial_print_val("SFX getStatus()",stat);
    while(stat != MP3_STATUS_STOPPED)
    {
         // waiting for mp3 to finish
         // debug
         delay(150);
         serial_print_val("SFX getStatus()",stat);
    }
    serial_print("SFX done");
  }
  // return;
}

// needed for JQ6500, because cheap crap.
void AudioFX::play_sample(uint8_t track, int playTime) {
  if (SFX_ADAFRUIT) {
    serial_print("b. SFX playing on Adafruit device");
    sfx->playTrack(track);
    delay(playTime);
  }
  else
  {
    serial_print("b. SFX playing on JQ6500 device");
    jfx->playFileByIndexNumber(track);
    delay(playTime);
  }
  serial_print("SFX done");
  // return;
}

void AudioFX::stop_play() {
    // may need to test status first 
    serial_print("Pausing JQ6500 device");
    jfx->pause();

}
