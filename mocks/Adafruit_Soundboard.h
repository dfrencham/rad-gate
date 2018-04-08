#pragma once
#ifndef _ADAFRUIT_SOUNDBOARD_H_
#define _ADAFRUIT_SOUNDBOARD_H_

#include <Arduino.h>

#define LINE_BUFFER_SIZE  80
#define MAXFILES 25

class Adafruit_Soundboard : public Print {
 public:
    Adafruit_Soundboard(Stream *s, Stream *d, int8_t r);
    boolean playTrack(uint8_t n);
    boolean playTrack(char *name);

 private:
  Stream   *stream;     // -> sound board, e.g. SoftwareSerial or Serial1
  Stream    *debug;      // -> host, e.g. Serial
  
  int8_t reset_pin;
  char line_buffer[LINE_BUFFER_SIZE];
  boolean writing;

  // File name & size caching
  uint8_t files;
  char filenames[MAXFILES][12];
  uint32_t filesizes[MAXFILES];

  //virtual size_t write(uint8_t); // Because Print subclass
};
#endif