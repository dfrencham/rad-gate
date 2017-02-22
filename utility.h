/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  utility.h
 *  (c) Danny Frencham 2017
 *****************************************/

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

void serial_print(const char* print_string);
void serial_print_val(const char* print_string, unsigned long print_val);
void chase(Adafruit_NeoPixel strip, uint32_t c);
int aprintf(char *str, ...);
