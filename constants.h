/*****************************************
 *  constants.h 
 *  (c) Danny Frencham 2017
 *****************************************/

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

// sounds
uint8_t SFX_PREP = 3;
uint8_t SFX_WATCH_GATE = 1;

// colors
/*chase(strip.Color(255, 0, 0)); // Red
chase(strip.Color(0, 255, 0)); // Green
chase(strip.Color(0, 0, 255)); // Blue
chase(strip.Color(44, 42, 0)); // yellow
chase(strip.Color(24, 0, 24)); // magenta
chase(strip.Color(44, 21, 0)); // redest orange
chase(strip.Color(255, 40, 5)); // orange
*/

struct gate_step {
  int tone_length;
  int wait_length;
  int light_num;
};


struct gate_step gate_steps[] =  {
  { DELAY_DROP_TONE_MS, 0, 1 },
  { 0, 60, 0 },
  { DELAY_DROP_TONE_MS, 0, 2 },
  { 0, 60, 0 },
  { DELAY_DROP_TONE_MS, 0, 3 },
  { 0, 60, 0 },
  { DELAY_DROP_TONE_FINAL_MS, 0, 4 }
};
