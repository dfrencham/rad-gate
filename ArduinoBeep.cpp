#include "ArduinoBeep.h"

ArduinoBeep::ArduinoBeep() { 
}

void ArduinoBeep::tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  tone(_pin, frequency, duration);
}

void ArduinoBeep::tone(uint8_t _pin, unsigned int frequency) {
  tone(_pin, frequency);
}

void ArduinoBeep::noTone(uint8_t _pin) {
  noTone(_pin);
}
