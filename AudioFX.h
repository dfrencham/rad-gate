/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#ifndef UNIT_TEST
#include "Adafruit_Soundboard.h"
#include "JQ6500_Serial.h"
#else
#include "mocks/Adafruit_Soundboard.h"
#include "mocks/JQ6500_Serial.h"
#endif
#include "ArduinoBeep.h"

#ifndef _AUDIO_H
#define _AUDIO_H

class AudioFX {

  public:

    AudioFX(Adafruit_Soundboard *sbref, ArduinoBeep *beepref);
    AudioFX(JQ6500_Serial *jref, ArduinoBeep *beepref);
    void start_tone(int hz);
    void stop_tone();
    void play_sound_samples();
    void play_abort();
    void play_power_on();

  private:
    Adafruit_Soundboard *sfx;
    JQ6500_Serial *jfx;
    ArduinoBeep *beep;
    void play_sample(uint8_t track);
    void play_sample(uint8_t track, int playTime);
};

#endif
