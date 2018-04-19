#include "MockBeep.h"
using namespace std;
#include <iostream>
//#include "Arduino.h"

const int TONE_SIZE = 20;
unsigned int toneCalls[TONE_SIZE] = { };
int tonePos = 0;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
