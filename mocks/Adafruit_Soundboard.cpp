#include <Arduino.h>
#include "Adafruit_Soundboard.h"

// Constructor
Adafruit_Soundboard::Adafruit_Soundboard(Stream *s, Stream *d, int8_t r) 
  : stream(s), debug(d), reset_pin(r) 
{
  writing = false;
  files = 0;
}

boolean Adafruit_Soundboard::playTrack(uint8_t n) {
  return true;
}

boolean Adafruit_Soundboard::playTrack(char *name) {
  return true;
}