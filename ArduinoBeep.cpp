#include "ArduinoBeep.h"
#include <iostream>

ArduinoBeep::ArduinoBeep() { 
  //std::cerr << CYAN << "ArduinoBeep()" << RESET << std::endl;
}

void ArduinoBeep::tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  //std::cerr << CYAN << "ArduinoBeep.tone() " << YELLOW << frequency << RESET << std::endl;
  tone(_pin, frequency, duration);
}

void ArduinoBeep::tone(uint8_t _pin, unsigned int frequency) {
  //std::cerr << CYAN << "ArduinoBeep.tone()" << YELLOW << frequency << RESET << std::endl;
  tone(_pin, frequency);
}

void ArduinoBeep::noTone(uint8_t _pin) {
  noTone(_pin);
}
