/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#ifndef UNIT_TEST
#include "Adafruit_NeoPixel.h"
#else
#include "mocks/Adafruit_NeoPixel.h"
#endif

#include <Arduino.h>
#include "utility.h"
#include "Gate.h"

#ifndef _LIGHTREE_H
#define _LIGHTREE_H

class LightTree {

  public:

    LightTree();

    void initialise(bool useRelays, int pin);
    void light_set(int step, Gate* gate);
    void led_reset();
    void abort();
    void ready();
    void set_status(uint32_t color);
    Adafruit_NeoPixel getStrip();

  private:
    Adafruit_NeoPixel _strip;
    void light_set_pixel(int step);
    void light_set_relay(int step);

};

#endif
