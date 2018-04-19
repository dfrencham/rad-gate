#ifndef _BEEPG_H
#define _BEEPG_H

#include <stdint.h> 

class Beep {
   public:
      // pure virtual function
      //virtual double getVolume() = 0;
      Beep();
      virtual void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) = 0;
      virtual void tone(uint8_t _pin, unsigned int frequency) = 0;
      virtual void noTone(uint8_t _pin) = 0;
};

#endif