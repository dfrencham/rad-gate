#include <stdint.h> 
#include "Adafruit_NeoPixel.h"
#include "mockConstants.h"
using namespace std;
#include <iostream>

const int NEO_PIXEL_SIZE = 100;
unsigned int neoPixelCalls[NEO_PIXEL_SIZE] = { };
int neoPixelCallPos = 0;

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p, neoPixelType t)
{
}

Adafruit_NeoPixel::Adafruit_NeoPixel() {
}

Adafruit_NeoPixel::~Adafruit_NeoPixel() {
}

void Adafruit_NeoPixel::addCall(unsigned int index) {
  neoPixelCalls[neoPixelCallPos] = index;
  neoPixelCallPos++;
}

bool Adafruit_NeoPixel::wasPixelLit(unsigned int index) {
  bool found = false;
  for(int i = 0; i<NEO_PIXEL_SIZE; i++) {
    if (neoPixelCalls[i] == index) {
      found = true;
    }
  }
  string foundString = found ? " true" : " false";
  cerr << GREEN << "      wasPixelLit " << index << CYAN << foundString << RESET << endl;
  return found;
}

void Adafruit_NeoPixel::begin(void) {
}

void Adafruit_NeoPixel::show(void) {

}

void Adafruit_NeoPixel::setPin(uint8_t p) {
}

void Adafruit_NeoPixel::Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  addCall(n);
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  addCall(n);
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint32_t c) {
  addCall(n);
}

void Adafruit_NeoPixel::setBrightness(uint8_t) {

}

void Adafruit_NeoPixel::clear() {

}

uint16_t Adafruit_NeoPixel::numPixels(void) const {
  return 8;
}

