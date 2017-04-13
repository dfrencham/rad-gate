/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "Adafruit_Soundboard.h"
#include <JQ6500_Serial.h>

#ifndef _AUDIO_H
#define _AUDIO_H

class AudioFX {

  public:

    AudioFX(Adafruit_Soundboard *sbref);
    AudioFX(JQ6500_Serial *jref);
    void start_tone(int hz);
    void stop_tone();
    void play_sound_samples();
    void play_abort();
    void play_power_on();

  private:
    Adafruit_Soundboard *sfx;
    JQ6500_Serial *jfx;
    void play_sample(uint8_t track);
    void play_sample(uint8_t track, int playTime);
};

#endif
