#include "MockBeep.h"
#include "mockConstants.h"
using namespace std;
#include <iostream>
//#include "Arduino.h"

const int TONE_SIZE = 20;
unsigned int toneCalls[TONE_SIZE] = { };
int tonePos = 0;

MockBeep::MockBeep() { 
  // cerr << "MockBeep()" << endl;
}

void MockBeep::tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
  //tone(_pin, frequency, duration);
  // cerr << "addToneCall()" << endl;
  addToneCall(frequency);
}

void MockBeep::tone(uint8_t _pin, unsigned int frequency) {
  //tone(_pin, frequency);
  // cerr << "addToneCall()" << endl;
  addToneCall(frequency);
}

void MockBeep::noTone(uint8_t _pin) {
  //noTone(_pin);
}

void MockBeep::addToneCall(unsigned int frequency) {
  toneCalls[tonePos] = frequency;
  tonePos++;
  // if ((unsigned int)tonePos >= sizeof(toneCalls)) {
  //   cerr << "addToneCall() tone array reset" << endl;
  //   tonePos = 0;
  // }
  // cerr << "addToneCall() tonePos " << tonePos << endl;
}

bool MockBeep::wasTonePlayed(unsigned int frequency) {
  bool found = false;
  for(int i = 0; i<TONE_SIZE; i++) {
    if (toneCalls[i] == frequency) {
      found = true;
    }
  }
  cerr << GREEN << "      wasTonePlayed() " << frequency << CYAN << found << RESET << endl;
  return found;
}
