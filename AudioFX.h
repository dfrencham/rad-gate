/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "Adafruit_Soundboard.h"

#ifndef _AUDIO_H
#define _AUDIO_H

class AudioFX {

  public:

    AudioFX(Adafruit_Soundboard *sbref);
    void start_tone(int hz);
    void stop_tone();
    void play_sound_samples();
    void play_abort();

  private:
    Adafruit_Soundboard *sfx;

};

#endif
