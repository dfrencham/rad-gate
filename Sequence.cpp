/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/
 /**************************************************
  Action Plan for the latter part of sequence

 ItemTime(ms)Action1  Action2          Action3
  0    0     Set LED1  Play Tone 632 
  1   60               Stop Tone 
  2  120     Set LED2  Play Tone 632 
  3  180               Stop Tone 
  4  240     Set LED3  Play Tone 632 
  5  300               Stop Tone 
  6  360     Set LED4  Play Tone 632   Gate Activate
  7  660                               Gate Deactivate
  8 2610    Reset LEDS  Stop Tone
  *****************************************************/

#include "constants.h"
#include "utility.h"
#include "Sequence.h"

volatile long sensor_time = 0;
unsigned long gate_drop_start = 0;
volatile bool gotInterrupt2 = false;
extern void end_seq(volatile long react_time);

Sequence::Sequence(Gate* gateOb, AudioFX* audioOb, LightTree* lighttreeOb)
{
  gate = gateOb;
  audio = audioOb;
  lighttree = lighttreeOb;
  pinMode(PIN_SENSOR, INPUT_PULLUP);
}

void Interrupt2() {
  if (gotInterrupt2 == false) {
    gotInterrupt2 = true;
    sensor_time = millis() - gate_drop_start; 
    end_seq(sensor_time);    
  }
}

void Sequence::begin_sequence() {
    
    int T0 = 0;                         
    int T1 = T0 + DELAY_DROP_TONE_MS;   
    int T2 = T1 + DELAY_INTERVAL_MS;     
    int T3 = T2 + DELAY_DROP_TONE_MS;  
    int T4 = T3 + DELAY_INTERVAL_MS;    
    int T5 = T4 + DELAY_DROP_TONE_MS;  
    int T6 = T5 + DELAY_INTERVAL_MS;   
    int T7 = T6 + GATE_ACTIVE_MS;       
    int T8 = T6 + DELAY_DROP_TONE_FINAL_MS; 

    int target[] = {T0, T1, T2, T3, T4, T5, T6, T7, T8};

    int seq[][3] = { 
      { 1, 1,-1},
      {-1, 0,-1},
      { 2, 1,-1}, 
      {-1, 0,-1},
      { 3 ,1,-1},
      {-1, 0,-1},
      { 4, 1, 1},
      {-1,-1, 0},
      {-1, 0,-1},
    };

    int count = 9;
    int step = 0;
    unsigned long offset;
    unsigned long now = 0;
    int val;

  serial_print("Sequence begin");

  gate->set_sequence_running(true);

  digitalWrite(LED_BUILTIN, HIGH);  // turn on builtin LED
  digitalWrite(PIN_LED_ACTIVE, HIGH);  // turn on "Active" LED

  lighttree->led_reset();
  audio->play_sound_samples();
  gate->random_wait();

  // once the sequence starts, do not allow abort
  serial_print("No longer abortable");
  gate->set_abortable(false); 

  // Use interrupt to catch END request from SENSOR
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), Interrupt2, LOW);
  
  offset = millis();
  
  while((step < count) && (!gate->is_aborted())) {
    while (target[step] > now) {
      now = millis() - offset;
    }    
    for (int i=0; i<3; i++){
      val = seq[step][i];
 
      if (val >= 0){
        if (i == 0){
          setLed(val);
        }
        if (i == 1){
          playTone(val);
        }
        if (i == 2){
          gateAct(val);
        }              
      }
    }
    step++;
  }
    
  serial_print("Setting sequence to STOP");
  gate->set_sequence_running(false);

  if (!gate->is_aborted()) {
    audio->stop_tone();
  }
  else {
    abort_seq();
    gate->set_abortable(true);
  }
  
  set_ready();

  digitalWrite(PIN_LED_ACTIVE, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  serial_print("Sequence complete - Waiting for reaction time...");
}

void Sequence::abort_seq() {
  serial_print("Sequence abort");
  lighttree->abort();
  audio->play_abort();
  lighttree->led_reset();
  delay(3000);
  set_ready();
}

void Sequence::set_ready() {
  lighttree->ready();
  gate->ready();
}

void Sequence::setLed(int val) {
  // Serial.print("Set LED On = ");
  // Serial.println(val);
  lighttree->light_set(val);
}

void Sequence::playTone(int val){
  // Serial.print("Play tone 632Hz = "); 
  // Serial.println(val);
  if (val == 0) {
    audio->stop_tone();
  }
  else if (val == 1) {
    audio->start_tone(TONE_DROP_HZ);
  }
}
             
void Sequence::gateAct(int val){
  // Serial.print("Gate activation = ");
  // Serial.println(val);
  if (val == 1) {
    gate_drop_start = millis();
    gate->drop(); // turn on solenoid
    gotInterrupt2 = false;
  }
  else if (val == 0) {
    gate->arm(); // turn off solenoid
  }
}

void end_seq(volatile long react_time) {
  serial_print_val("Reaction Time =", react_time);
  serial_print("Press GO to restart...");  
}
