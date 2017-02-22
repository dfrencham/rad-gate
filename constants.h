/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <Adafruit_NeoPixel.h>

#define VERSION "0.5.0"

#define DELAY_DROP_TONE_MS 60
#define DELAY_DROP_TONE_FINAL_MS 2250
#define DELAY_GATE_RISE_WARN_MS 25
#define DELAY_ABORT_TONE_1_MS 220
#define DELAY_ABORT_TONE_2_MS 440

#define DELAY_RAND_MIN 100
#define DELAY_RAND_MAX 2700

#define TONE_DROP_HZ 632
#define TONE_GATE_RISE 1150
#define TONE_ABORT_1_HZ 740
#define TONE_ABORT_2_HZ 680

#define PIN_NEO_PIXEL 7
#define PIN_BUTTON_GO 2
#define PIN_SPEAKER 5
#define PIN_RELAY 4
#define PIN_LED_ACTIVE 9
#define PIN_GATE_STATUS_LED_RED 18
#define PIN_GATE_STATUS_LED_GREEN 19
#define SFX_TX 11
#define SFX_RX 10

#define SFX_RST 12
#define SFX_ACT 13

#define NUMPIXELS 8

#define ENABLE_VOICE_CADENCE 1

// colours
extern uint32_t ORANGE;
extern uint32_t RED;
extern uint32_t GREEN;
extern uint32_t YELLOW;
extern uint32_t BLUE;
extern uint32_t WHITE;

// sounds
extern uint8_t SFX_PREP;
extern uint8_t SFX_WATCH_GATE;

//struct gate_steps;
typedef struct {
  unsigned long  tone_length;
  unsigned long  wait_length;
  int light_num;
} gate_step;

#endif
