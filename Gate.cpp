/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "constants.h"
#include "utility.h"
#include "Gate.h"

int FLAG_ABORT_DROP = 0;
int FLAG_SEQUENCE_RUNNING = 0;
int FLAG_IGNORE_INTERRUPT = 1;

Gate::Gate(){

}

void Gate::random_wait() {
  int rand_delay = random(DELAY_RAND_MIN,DELAY_RAND_MAX+1);
  unsigned long wait_timer = millis() + rand_delay;
  serial_print_val("Gate sequence random wait time",rand_delay);
  serial_print_val("Wait timer",wait_timer);
  serial_print_val("Millis",millis());
  while((millis() < wait_timer) && (!FLAG_ABORT_DROP)) {
    // waiting for random wait to finish
  }
  serial_print("Wait timer done");
}

void Gate::ready(){
  FLAG_ABORT_DROP = 0;
}

void Gate::arm() {
  // set LED to red
  // turn on electro magnet
  // beep
}

void Gate::abort() {
  FLAG_ABORT_DROP = 1;
}

void Gate::drop() {
  digitalWrite(PIN_RELAY, LOW);
}

bool Gate::is_sequence_running() {
  return !!FLAG_SEQUENCE_RUNNING;
}

bool Gate::is_aborted() {
  return !!FLAG_ABORT_DROP;
}

bool Gate::is_abortable() {
  return !FLAG_IGNORE_INTERRUPT;
}

void Gate::set_sequence_running(bool running) {
  FLAG_SEQUENCE_RUNNING = running;
  FLAG_IGNORE_INTERRUPT = false;
}

void Gate::set_abortable(bool abortable) {
  FLAG_IGNORE_INTERRUPT = !abortable;
}
