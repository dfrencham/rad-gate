#ifndef _ARDUINOBEEP_H
#define _ARDUINOBEEP_H

#include <stdint.h> 
#include "Beep.h"

class ArduinoBeep : public Beep {
    public:
      ArduinoBeep();
      void tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
      void tone(uint8_t _pin, unsigned int frequency);
      void noTone(uint8_t _pin);
};

#endif