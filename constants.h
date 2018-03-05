/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <Adafruit_NeoPixel.h>

#define VERSION "0.8.0"

// uncomment for RGBW (for real Neopixels)
//#define HARDWARE_NEOPIXEL_RGBW
// uncomment for RGB (usually cheap Neopixel clones)
#define HARDWARE_NEOPIXEL_RGB

// uncomment if using Adafruit sound fx boards
//#define HARDWARE_SOUNDBOARD_ADAFRUIT
// set to "JQ6500" if using the cheap and friendly Aliexpress JQ6500
#define HARDWARE_SOUNDBOARD_JQ6500 1

#define DELAY_INTERVAL_MS 60
#define DELAY_DROP_TONE_MS 60
#define DELAY_DROP_TONE_FINAL_MS 2250
#define DELAY_GATE_RISE_WARN_MS 25
#define DELAY_ABORT_TONE_1_MS 220
#define DELAY_ABORT_TONE_2_MS 440
#define GATE_ACTIVE_MS 300

// random start min and max
#define DELAY_RAND_MIN 100
#define DELAY_RAND_MAX 2700

// some inferior gate controllers don't BEEP at the correct pitch
// frequence. Correct tones (in Hz) are below
#define TONE_DROP_HZ 632
#define TONE_GATE_RISE 1150
#define TONE_ABORT_1_HZ 740
#define TONE_ABORT_2_HZ 680
#define TONE_VOLUME 130

#define PIN_NEO_PIXEL 13 // light tree pin
#define PIN_BUTTON_GO 2  // The GO/ABORT button -interrupt 
#define PIN_SPEAKER 11  // tone output
#define PIN_RELAY 8 // relay, or MOSFET for GATE
#define PIN_LED_ACTIVE 5  // On when GO button activated 
#define PIN_GATE_STATUS_LED_RED 18 // Not used
#define PIN_GATE_STATUS_LED_GREEN 19  //Not used
#define PIN_SFX_TX 10 // sound board transmit (Arduino Rx)
#define PIN_SFX_RX 9 // sound board receive (Arduino Tx)
#define PIN_SENSOR 3 // light sensor - interrupt

#define PIN_SFX_RST 0 // sound board reset
#define PIN_SFX_ACT 1 // sound board active

#define PIN_LIGHT_TREE_RELAY_ENABLE 4
#define PIN_LIGHT_TREE_RELAY_1 14
#define PIN_LIGHT_TREE_RELAY_2 15
#define PIN_LIGHT_TREE_RELAY_3 16
#define PIN_LIGHT_TREE_RELAY_4 17

#define NUMPIXELS 8 // how many LEDS do you have?

#define ENABLE_VOICE_CADENCE 1

// colours
extern uint32_t ORANGE;
extern uint32_t RED;
extern uint32_t GREEN;
extern uint32_t YELLOW;
extern uint32_t BLUE;
extern uint32_t WHITE;

extern uint32_t RGB_ORANGE;
extern uint32_t RGB_GREEN;
extern uint32_t RGB_RED;
extern uint32_t RGB_YELLOW;
extern uint32_t RGB_BLUE;
extern uint32_t RGB_PURPLE;
extern uint32_t RGB_WHITE;

// sounds
extern uint8_t SFX_PREP;
extern uint8_t SFX_WATCH_GATE;

#endif
