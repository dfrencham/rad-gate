/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  LightTree.h
 *  (c) Danny Frencham 2017
 *****************************************/

#include <Adafruit_NeoPixel.h>
#include "utility.h"
#include "Gate.h"

#ifndef _LIGHTREE_H
#define _LIGHTREE_H

class LightTree {

  public:

    LightTree(int pin);

    void light_start_seq_led(int step, Gate* gate);
    void led_reset();
    void abort();
    void ready();
    void set_status(uint32_t color);

  private:
    Adafruit_NeoPixel _strip;

};

#endif
