/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  LightTree.cpp
 *  (c) Danny Frencham 2017
 *****************************************/

#include <Adafruit_NeoPixel.h>
#include "constants.h"
#include "LightTree.h"

LightTree::LightTree(int pin) {

  _strip = Adafruit_NeoPixel(8, pin, NEO_RGBW + NEO_KHZ800);
  _strip.begin();
  _strip.setBrightness(255);
}

void LightTree::light_start_seq_led(int step, Gate* gate) {
  serial_print_val("Set LED", step);
  switch (step) {
    case 1:
      led_reset();
      _strip.setPixelColor(6, RED);
      _strip.setPixelColor(7, RED);
      break;
    case 2:
      _strip.setPixelColor(4, YELLOW);
      _strip.setPixelColor(5, YELLOW);
      break;
    case 3:
      _strip.setPixelColor(2, YELLOW);
      _strip.setPixelColor(3, YELLOW);
      break;
    case 4:
      gate->drop();
      _strip.setPixelColor(0, GREEN);
      _strip.setPixelColor(1, GREEN);
      break;
     default:
      led_reset();
  }
  _strip.show();
}

void LightTree::led_reset() {
  for(int i=0;i<8;i++) {
    _strip.setPixelColor(i,0,0,0,0);
  }
  _strip.show();
}

void LightTree::abort() {
  led_reset();
  for(int i=0;i<8;i++) {
    _strip.setPixelColor(i,RED);
  }
  _strip.show();
}

void LightTree::ready() {
  led_reset();
  _strip.setPixelColor(0, BLUE);
  _strip.show();
}

void LightTree::set_status(uint32_t color) {
  led_reset();
  _strip.setPixelColor(0, color);
  _strip.show();
}
