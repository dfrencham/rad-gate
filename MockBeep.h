#ifndef _MOCKBEEP_H
#define _MOCKBEEP_H

#include "ArduinoBeep.h"

class MockBeep : public ArduinoBeep {
    public:
      MockBeep();
      static MockBeep* instance;

      void tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
      void tone(uint8_t _pin, unsigned int frequency);
      void noTone(uint8_t _pin);

    private:
      void addToneCall(unsigned int frequency);
      bool wasTonePlayed(unsigned int frequency);
      static MockBeep* getInstance();
};

#endif