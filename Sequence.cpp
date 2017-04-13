/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "constants.h"
#include "utility.h"
#include "Sequence.h"

Sequence::Sequence(Gate* gateOb, AudioFX* audioOb, LightTree* lighttreeOb)
{
  gate = gateOb;
  audio = audioOb;
  lighttree = lighttreeOb;
}

void Sequence::begin_sequence() {

  // gate timings
  // Tone Play Time, wait length, light tree step
  gate_step gate_steps[] =  {
    { DELAY_DROP_TONE_MS, 0, 1 },
    { 0, 60, 0 },
    { DELAY_DROP_TONE_MS, 0, 2 },
    { 0, 60, 0 },
    { DELAY_DROP_TONE_MS, 0, 3 },
    { 0, 60, 0 },
    { DELAY_DROP_TONE_FINAL_MS, 0, 4 },
    { 0, 0, 0 }  
  };

  serial_print("Sequence begin");

  gate->set_sequence_running(true);
  int step = 0;
  int playing_tone = 0;
  int waiting = 0;
  unsigned long timer_start = 0;
  int gate_step_count = 7; // can't programatically count dynamic array

  digitalWrite(LED_BUILTIN, HIGH);  // turn on LED
  digitalWrite(PIN_LED_ACTIVE, HIGH);  // turn on LED

  lighttree->led_reset();
  audio->play_sound_samples();
  gate->random_wait();

  gate->set_abortale(false); // once the sequence starts, do not allow abort
  while((step < gate_step_count) && (!gate->is_aborted())) {
    unsigned long now = millis();
    unsigned long timer = now - timer_start;

    if (playing_tone && (timer >= gate_steps[step].tone_length)) {
      // reset timer
      playing_tone = 0;
      serial_print_val("Stop tone",step);
      serial_print_val("Tone length",gate_steps[step].tone_length);
      audio->stop_tone();
      step++;
    }
    if (!playing_tone && (gate_steps[step].tone_length > 0)) {
      timer_start = now;
      audio->start_tone(TONE_DROP_HZ);
      serial_print_val("LED step",step);
      lighttree->light_start_seq_led(gate_steps[step].light_num, gate);
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
    gate->set_sequence_running(false);
  }
  gate->set_sequence_running(false);

  if (!gate->is_aborted()) {
    audio->stop_tone();
  }
  else
  {
    abort_seq();
  }
  set_ready();

  digitalWrite(PIN_LED_ACTIVE, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PIN_RELAY, HIGH); // turn on magnet
  serial_print("Sequence complete");
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
