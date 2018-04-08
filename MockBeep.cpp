#include "MockBeep.h"
//#include "Arduino.h"

unsigned int toneCalls[20];
int tonePos = 0;

MockBeep::MockBeep() { 
}

void MockBeep::tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  //tone(_pin, frequency, duration);
  addToneCall(frequency);
}

void MockBeep::tone(uint8_t _pin, unsigned int frequency) {
  //tone(_pin, frequency);
  addToneCall(frequency);
}

void MockBeep::noTone(uint8_t _pin) {
  //noTone(_pin);
}

void MockBeep::addToneCall(unsigned int frequency) {
  toneCalls[tonePos] = frequency;
  tonePos++;
  if (sizeof(toneCalls) >= (unsigned int)tonePos) {
    tonePos = 0;
  }
}

bool MockBeep::wasTonePlayed(unsigned int frequency) {
  bool found = false;
  for(int i; i<((signed int)sizeof(toneCalls)); i++) {
    if (toneCalls[i] == frequency) {
      found = true;
    }
  }
  return found;
}
