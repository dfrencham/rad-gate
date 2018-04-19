#ifndef _MOCKBEEP_H
#define _MOCKBEEP_H

#include "Beep.h"

class MockBeep : public Beep {
    public:
      MockBeep();

      void tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
      void tone(uint8_t _pin, unsigned int frequency);
      void noTone(uint8_t _pin);
      void addToneCall(unsigned int frequency);
      bool wasTonePlayed(unsigned int frequency);

    private:
      // static MockBeep* getInstance();
};

#endif