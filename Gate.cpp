/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include "constants.h"
#include "utility.h"
#include "Gate.h"

int FLAG_ABORT_PENDING = 0;
int FLAG_SEQUENCE_RUNNING = 0;
int FLAG_IS_ABORTABLE = 0;

Gate::Gate(){

}

void Gate::random_wait() {
  int rand_delay = random(DELAY_RAND_MIN,DELAY_RAND_MAX+1);
  unsigned long wait_timer = millis() + rand_delay;
  serial_print_val("Gate sequence random wait time",rand_delay);
  // serial_print_val("Wait timer",wait_timer);
  // serial_print_val("Millis",millis());
  while((millis() < wait_timer) && (!FLAG_ABORT_PENDING)) {
    // waiting for random wait to finish
  }
  serial_print("Wait timer done");
}

void Gate::ready(){
  FLAG_ABORT_PENDING = 0;
  FLAG_IS_ABORTABLE = 0;
}

void Gate::arm() {
  serial_print("Gate Deactivate");
  digitalWrite(PIN_RELAY, LOW);
}

void Gate::abort() {
  FLAG_ABORT_PENDING = 1;
}

void Gate::drop() {
  serial_print("Gate Activate");
  digitalWrite(PIN_RELAY, HIGH);
}

bool Gate::is_sequence_running() {
  return !!FLAG_SEQUENCE_RUNNING;
}

bool Gate::is_aborted() {
  return !!FLAG_ABORT_PENDING;
}

bool Gate::is_abortable() {
  return FLAG_IS_ABORTABLE && !FLAG_ABORT_PENDING;
}

void Gate::set_sequence_running(bool running) {
  FLAG_SEQUENCE_RUNNING = running;
  FLAG_IS_ABORTABLE = 1;
}

void Gate::set_abortable(bool abortable) {
  FLAG_IS_ABORTABLE = abortable;
}
