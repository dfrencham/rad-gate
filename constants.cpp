/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <stdint.h> 

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
// uint32_t GetColor(uint8_t r, uint8_t g, uint8_t b) {
//   return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
// }

// Convert separate R,G,B,W into packed 32-bit WRGB color.
// Packed format is always WRGB, regardless of LED strand color order.
// uint32_t GetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
//   return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
// }

// colours
uint32_t ORANGE = 16737280;
uint32_t RED = 65280;
uint32_t GREEN = 16711680;
uint32_t YELLOW = 184549120;
uint32_t BLUE = 255;
uint32_t WHITE = 4278190080;

uint32_t RGB_ORANGE = 9848320;
uint32_t RGB_GREEN = 30720;
uint32_t RGB_RED = 9830400;
uint32_t RGB_YELLOW = 16776960;
uint32_t RGB_BLUE = 255;
uint32_t RGB_PURPLE = 16711935;
uint32_t RGB_WHITE = 16777215;

uint8_t SFX_PREP = 1;
uint8_t SFX_WATCH_GATE = 2;
