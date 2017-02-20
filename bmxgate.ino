/*****************************************
 *  bmxgate.ino 
 *  (c) Danny Frencham 2017
 *****************************************/
 
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "constants.h"

// LED strip init
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN_NEO_PIXEL, NEO_RGBW + NEO_KHZ800);

// soundfx board init
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

int gate_step_count = 7; // can't programatically count dynamic array
int delayval = 500; // delay for half a second

// flags
int FLAG_BUTTON_PRESSED = 1;
int FLAG_ABORT_DROP = 0;
int FLAG_SEQUENCE_RUNNING = 0;
int FLAG_IGNORE_INTERRUPT = 1;
int FLAG_GATE_ARMED = 0; // gate is locked, ready for release trigger

// colours
uint32_t ORANGE = strip.Color(255, 100, 0);
uint32_t RED = strip.Color(0, 255, 0);
uint32_t GREEN = strip.Color(255, 0, 0, 0);
uint32_t YELLOW = strip.Color(255, 255, 0, 10);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t WHITE = strip.Color(0, 0, 0, 255);

// tracking variables
int currentStep = 0;

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_ACTIVE, OUTPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_BUTTON_GO, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(SFX_ACT, INPUT);
  //pinMode(PIN_REED_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(1), Interrupt1, RISING);
  digitalWrite(3, HIGH); // interrupt on 3
  digitalWrite(PIN_RELAY, LOW);
  
  strip.begin();
  strip.setBrightness(255);
  
  // init SFX serial
  ss.begin(9600);
  
  Serial.begin(115200);
  serial_print("Gate controller initialised");
}
 
void loop() {

  /*if (digitalRead(PIN_REED_SWITCH) == LOW) {
    set_status(GREEN);
  }
  else
  {
    set_status(BLUE);
  }*/

  if (digitalRead(PIN_BUTTON_GO) == LOW) {
    FLAG_BUTTON_PRESSED = 0; // reset
  }
  else if (digitalRead(PIN_BUTTON_GO) == HIGH)
  {
    if (FLAG_SEQUENCE_RUNNING) {
      FLAG_ABORT_DROP = 1;
    }
    if (!FLAG_BUTTON_PRESSED) {
      FLAG_BUTTON_PRESSED = 1;
      // do button press action
      //light_start_seq_led(getCurrentStep());
      begin_sequence();
      //abort_seq();
    }
    // else still holding button    
  }
}

int getCurrentStep() {
  currentStep++;
  if (currentStep > 4)
    currentStep = 1;
  return currentStep;
}

// likely needs an interrupt
void begin_sequence() {

  serial_print("Sequence begin");

  FLAG_ABORT_DROP = 0;
  FLAG_SEQUENCE_RUNNING = 1;
  FLAG_IGNORE_INTERRUPT = 0;
  unsigned long start_time = millis();
  int step = 0;
  int playing_tone = 0;
  int waiting = 0;
  unsigned long timer_start = 0;

  //digitalWrite(LED_BUILTIN, HIGH);  // turn on LED
  digitalWrite(PIN_LED_ACTIVE, HIGH);  // turn on LED

  led_reset();

  play_sound_samples();
  
  //printf("array %lu \n", sizeof(&gate_steps)-1);
  int rand_delay = random(DELAY_RAND_MIN,DELAY_RAND_MAX+1); 
  unsigned long wait_timer = millis() + rand_delay;
  serial_print_val("Random wait time",rand_delay); 
  serial_print_val("Wait timer",wait_timer); 
  serial_print_val("Millis",millis()); 
  while((millis() < wait_timer) && (!FLAG_ABORT_DROP)) {
    // waiting for random wait to finish
  }
  serial_print("Wait timer done");
  FLAG_IGNORE_INTERRUPT = 1;
  
  while((step < gate_step_count) && (!FLAG_ABORT_DROP)) {
    unsigned long now = millis();
    unsigned long timer = now - timer_start;

    if (playing_tone && (timer >= gate_steps[step].tone_length)) {
      // reset timer
      playing_tone = 0;
      stop_tone();
      step++;
    }
    if (!playing_tone && (gate_steps[step].tone_length > 0)) {
      timer_start = now;
      start_tone(TONE_DROP_HZ);
      light_start_seq_led(gate_steps[step].light_num);
      playing_tone = 1;
    }
    if (waiting && (timer >= gate_steps[step].wait_length)) {
      waiting = 0;
      step++;
    }
    if (!waiting && (gate_steps[step].wait_length > 0)) {
      timer_start = now;
      waiting = 1;
    }
    FLAG_SEQUENCE_RUNNING = 0;
  }
  FLAG_SEQUENCE_RUNNING = 0;
  stop_tone();
  if (FLAG_ABORT_DROP) {
    //abort_seq();
    FLAG_ABORT_DROP = 0;
  }
  set_ready();

  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PIN_LED_ACTIVE, LOW);
  digitalWrite(PIN_RELAY, LOW);
  serial_print("Sequence complete");
}

void play_sound_samples() {
  if (!ENABLE_VOICE_CADENCE) {
    serial_print("Skipping voice cadence");
    return;
  }
    
  serial_print("Play Sample1");
  sfx.playTrack(SFX_PREP);
  delay(50);
  while (digitalRead(SFX_ACT) == LOW) {
    // wait for sample to finish
  }
  delay(1750);
  serial_print("Play Sample2");
  sfx.playTrack(SFX_WATCH_GATE);
  delay(50);
  while (digitalRead(SFX_ACT) == LOW) {
    // wait for sample to finish
  }
  serial_print("SFX Done");
}

void light_start_seq_led(int step) {
  serial_print_val("Set LED", step);
  switch (step) {
    case 1:
      led_reset(); 
      strip.setPixelColor(6, RED);
      strip.setPixelColor(7, RED);
      break;
    case 2:
      strip.setPixelColor(4, YELLOW);
      strip.setPixelColor(5, YELLOW);
      break;
    case 3:
      strip.setPixelColor(2, YELLOW);
      strip.setPixelColor(3, YELLOW);
      break;
    case 4:
      drop_gate();
      strip.setPixelColor(0, GREEN);
      strip.setPixelColor(1, GREEN);
      break;
     default:
      led_reset();
  }
  strip.show();
}

void led_reset() {
  for(int i=0;i<8;i++) {
    strip.setPixelColor(i,0,0,0,0);
  }
  strip.show();
}

void start_tone(int hz) {
  tone(PIN_SPEAKER, TONE_DROP_HZ);
}

void stop_tone() {
  noTone(PIN_SPEAKER);
}

void abort_seq() {
  serial_print("Sequence abort");
  for(int i=0;i<8;i++) {
    strip.setPixelColor(i,RED);
  }
  strip.show();
  tone(PIN_SPEAKER, TONE_ABORT_1_HZ, DELAY_ABORT_TONE_1_MS);
  delay(DELAY_ABORT_TONE_1_MS);
  tone(PIN_SPEAKER, TONE_ABORT_2_HZ, DELAY_ABORT_TONE_2_MS);
  led_reset();
  delay(3000);
  set_ready();
}

void set_ready() {
  led_reset();
  strip.setPixelColor(0, BLUE);
  strip.show();
  FLAG_ABORT_DROP = 0;
}

void set_status(uint32_t color) {
  led_reset();
  strip.setPixelColor(0, color);
  strip.show();
}

void drop_gate() {
  // if gate armed
    // trigger relay drop
    // set gate LED to green   
    digitalWrite(PIN_RELAY, HIGH);
}

// called when reed sensor triggered
void arm_gate() {
  // set LED to red

  // turn on electro magnet

  // beep
 
}

// interrrupt
void Interrupt1()
{
  if (!FLAG_ABORT_DROP && !FLAG_IGNORE_INTERRUPT) {
    serial_print("Interrupt triggered");
    FLAG_ABORT_DROP = 1;
    abort_seq();
  }
}


