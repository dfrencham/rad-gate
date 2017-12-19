/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <Adafruit_NeoPixel.h>
#include "constants.h"
#include "LightTree.h"

int rgbMode = 0;
bool modeRelay = false;

LightTree::LightTree() { }

void LightTree::initialise(bool useRelays, int pin) {
  if (useRelays) {
    modeRelay = useRelays;
    pinMode(PIN_LIGHT_TREE_RELAY_1, OUTPUT);
    pinMode(PIN_LIGHT_TREE_RELAY_2, OUTPUT);
    pinMode(PIN_LIGHT_TREE_RELAY_3, OUTPUT);
    pinMode(PIN_LIGHT_TREE_RELAY_4, OUTPUT);
    led_reset();
  } 
  else 
  {
    #ifdef HARDWARE_NEOPIXEL_RGB
      _strip = Adafruit_NeoPixel(8, pin, NEO_GRB + NEO_KHZ800);
      // need to use different colours for RGB stick
      rgbMode = 1;
    #endif
    #ifdef HARDWARE_NEOPIXEL_RGBW
      _strip = Adafruit_NeoPixel(8, pin, NEO_RGBW + NEO_KHZ800);
    #endif

    _strip.begin();
    // _strip.setBrightness(100); dull
    _strip.setBrightness(255); // blinding
  }
}

void LightTree::light_set(int step, Gate* gate) {
  serial_print_val("Set LED", step);
  switch (step) {
    case 1:
      led_reset();
      modeRelay ? light_set_relay(step) : light_set_pixel(step);
      break;
    case 2:
    case 3:
      modeRelay ? light_set_relay(step) : light_set_pixel(step);
      break;
    case 4:
      gate->drop();
      modeRelay ? light_set_relay(step) : light_set_pixel(step);
      break;
     default:
      led_reset();
  }
}

void LightTree::led_reset() {
  if (modeRelay) {
    digitalWrite(PIN_LIGHT_TREE_RELAY_1, HIGH);
    digitalWrite(PIN_LIGHT_TREE_RELAY_2, HIGH);
    digitalWrite(PIN_LIGHT_TREE_RELAY_3, HIGH);
    digitalWrite(PIN_LIGHT_TREE_RELAY_4, HIGH);
  } else {
    for(int i=0;i<8;i++) {
      _strip.setPixelColor(i,0,0,0,0);
    }
    _strip.show();
  }
}

void LightTree::abort() {
  if (modeRelay) {
    //digitalWrite(PIN_LIGHT_TREE_RELAY_1, HIGH);
    //led_reset();
    digitalWrite(PIN_LIGHT_TREE_RELAY_1, HIGH);
    digitalWrite(PIN_LIGHT_TREE_RELAY_2, LOW);
    digitalWrite(PIN_LIGHT_TREE_RELAY_3, LOW);
    digitalWrite(PIN_LIGHT_TREE_RELAY_4, HIGH);
  } else {
    led_reset();
    for(int i=0;i<8;i++) {
      _strip.setPixelColor(i,RED);
    }
    _strip.show();
  }
}

void LightTree::ready() {
  if (modeRelay) {
    led_reset();
  } else {
    led_reset();
    _strip.setPixelColor(0, BLUE);
    _strip.show();
  }
}

void LightTree::set_status(uint32_t color) {
  led_reset();
  _strip.setPixelColor(0, color);
  _strip.show();
}


void LightTree::light_set_pixel(int step) {
  switch (step) {
    case 1:
      led_reset();
      if (rgbMode) {
        _strip.setPixelColor(6, RGB_RED);
        _strip.setPixelColor(7, RGB_RED);
      } else {
        _strip.setPixelColor(6, RED);
        _strip.setPixelColor(7, RED);
      }
      break;
    case 2:
      if (rgbMode) {
        _strip.setPixelColor(4, RGB_ORANGE);
        _strip.setPixelColor(5, RGB_ORANGE);
      } else {
        _strip.setPixelColor(4, YELLOW);
        _strip.setPixelColor(5, YELLOW);
      }
      break;
    case 3:
      if (rgbMode) {
        _strip.setPixelColor(2, RGB_ORANGE);
        _strip.setPixelColor(3, RGB_ORANGE);
      } else {
        _strip.setPixelColor(2, YELLOW);
        _strip.setPixelColor(3, YELLOW);
      }
      break;
    case 4:
      if (rgbMode) {
        _strip.setPixelColor(0, RGB_GREEN);
        _strip.setPixelColor(1, RGB_GREEN);
      } else {
        _strip.setPixelColor(0, GREEN);
        _strip.setPixelColor(1, GREEN);
      }
      break;
     default:
      led_reset();
  }
  _strip.show();
}

void LightTree::light_set_relay(int step) {
  switch (step) {
    case 1:
      digitalWrite(PIN_LIGHT_TREE_RELAY_1, LOW);
      break;
    case 2:
      digitalWrite(PIN_LIGHT_TREE_RELAY_2, LOW);
      break;
    case 3:
      digitalWrite(PIN_LIGHT_TREE_RELAY_3, LOW);
      break;
    case 4:
      digitalWrite(PIN_LIGHT_TREE_RELAY_4, LOW);
      break;
     default:
      led_reset();
  }
}