#pragma once
#include <Arduino.h>
#include <stdint.h> 

#ifndef ADAFRUIT_NEOPIXEL_H
#define ADAFRUIT_NEOPIXEL_H

// RGB NeoPixel permutations; white and red offsets are always same
// Offset:         W          R          G          B
#define NEO_RGB  ((0 << 6) | (0 << 4) | (1 << 2) | (2))
#define NEO_RBG  ((0 << 6) | (0 << 4) | (2 << 2) | (1))
#define NEO_GRB  ((1 << 6) | (1 << 4) | (0 << 2) | (2))
#define NEO_GBR  ((2 << 6) | (2 << 4) | (0 << 2) | (1))
#define NEO_BRG  ((1 << 6) | (1 << 4) | (2 << 2) | (0))
#define NEO_BGR  ((2 << 6) | (2 << 4) | (1 << 2) | (0))

// RGBW NeoPixel permutations; all 4 offsets are distinct
// Offset:         W          R          G          B
#define NEO_WRGB ((0 << 6) | (1 << 4) | (2 << 2) | (3))
#define NEO_WRBG ((0 << 6) | (1 << 4) | (3 << 2) | (2))
#define NEO_WGRB ((0 << 6) | (2 << 4) | (1 << 2) | (3))
#define NEO_WGBR ((0 << 6) | (3 << 4) | (1 << 2) | (2))
#define NEO_WBRG ((0 << 6) | (2 << 4) | (3 << 2) | (1))
#define NEO_WBGR ((0 << 6) | (3 << 4) | (2 << 2) | (1))

#define NEO_RWGB ((1 << 6) | (0 << 4) | (2 << 2) | (3))
#define NEO_RWBG ((1 << 6) | (0 << 4) | (3 << 2) | (2))
#define NEO_RGWB ((2 << 6) | (0 << 4) | (1 << 2) | (3))
#define NEO_RGBW ((3 << 6) | (0 << 4) | (1 << 2) | (2))
#define NEO_RBWG ((2 << 6) | (0 << 4) | (3 << 2) | (1))
#define NEO_RBGW ((3 << 6) | (0 << 4) | (2 << 2) | (1))

#define NEO_GWRB ((1 << 6) | (2 << 4) | (0 << 2) | (3))
#define NEO_GWBR ((1 << 6) | (3 << 4) | (0 << 2) | (2))
#define NEO_GRWB ((2 << 6) | (1 << 4) | (0 << 2) | (3))
#define NEO_GRBW ((3 << 6) | (1 << 4) | (0 << 2) | (2))
#define NEO_GBWR ((2 << 6) | (3 << 4) | (0 << 2) | (1))
#define NEO_GBRW ((3 << 6) | (2 << 4) | (0 << 2) | (1))

#define NEO_BWRG ((1 << 6) | (2 << 4) | (3 << 2) | (0))
#define NEO_BWGR ((1 << 6) | (3 << 4) | (2 << 2) | (0))
#define NEO_BRWG ((2 << 6) | (1 << 4) | (3 << 2) | (0))
#define NEO_BRGW ((3 << 6) | (1 << 4) | (2 << 2) | (0))
#define NEO_BGWR ((2 << 6) | (3 << 4) | (1 << 2) | (0))
#define NEO_BGRW ((3 << 6) | (2 << 4) | (1 << 2) | (0))

#define NEO_KHZ800 0x0000 // 800 KHz datastream
#ifndef __AVR_ATtiny85__
#define NEO_KHZ400 0x0100 // 400 KHz datastream
#endif

#ifdef NEO_KHZ400
typedef uint16_t neoPixelType;
#else
typedef uint8_t  neoPixelType;
#endif


class Adafruit_NeoPixel {

 public:

  // Constructor: number of LEDs, pin number, LED type
  Adafruit_NeoPixel(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel(void);
  ~Adafruit_NeoPixel();

  void
    begin(void),
    show(void),
    setPin(uint8_t p),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w),
    setPixelColor(uint16_t n, uint32_t c),
    setBrightness(uint8_t),
    clear(),
    addCall(unsigned int index);
  uint16_t
    numPixels(void) const;
  bool
    wasPixelLit(unsigned int index);
 private:

  boolean
#ifdef NEO_KHZ400  // If 400 KHz NeoPixel support enabled...
    is800KHz,      // ...true if 800 KHz pixels
#endif
    begun;         // true if begin() previously called
  uint16_t
    numLEDs,       // Number of RGB LEDs in strip
    numBytes;      // Size of 'pixels' buffer below (3 or 4 bytes/pixel)
  int8_t
    pin;           // Output pin number (-1 if not yet set)
  uint8_t
    brightness,
   *pixels,        // Holds LED color values (3 or 4 bytes each)
    rOffset,       // Index of red byte within each 3- or 4-byte pixel
    gOffset,       // Index of green byte
    bOffset,       // Index of blue byte
    wOffset;       // Index of white byte (same as rOffset if no white)
  uint32_t
    endTime;       // Latch timing reference
#ifdef __AVR__
  volatile uint8_t
    *port;         // Output PORT register
  uint8_t
    pinMask;       // Output PORT bitmask
#endif

};

#endif