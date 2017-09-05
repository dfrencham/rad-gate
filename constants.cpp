/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <Adafruit_NeoPixel.h>

// colours
uint32_t ORANGE = Adafruit_NeoPixel::Color(255, 100, 0);
uint32_t RED = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t GREEN = Adafruit_NeoPixel::Color(255, 0, 0, 0);
uint32_t YELLOW = Adafruit_NeoPixel::Color(255, 255, 0, 10);
uint32_t BLUE = Adafruit_NeoPixel::Color(0, 0, 255);
uint32_t WHITE = Adafruit_NeoPixel::Color(0, 0, 0, 255);

uint32_t RGB_ORANGE = Adafruit_NeoPixel::Color(150, 70, 0);
uint32_t RGB_GREEN = Adafruit_NeoPixel::Color(0, 120, 0);
uint32_t RGB_RED = Adafruit_NeoPixel::Color(150, 0, 0);
uint32_t RGB_YELLOW = Adafruit_NeoPixel::Color(255, 255, 0);
uint32_t RGB_BLUE = Adafruit_NeoPixel::Color(0, 0, 255);
uint32_t RGB_PURPLE = Adafruit_NeoPixel::Color(255, 0, 255);
uint32_t RGB_WHITE = Adafruit_NeoPixel::Color(255, 255, 255);

uint8_t SFX_PREP = 1;
uint8_t SFX_WATCH_GATE = 2;
