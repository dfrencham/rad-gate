/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <Arduino.h>
#include "constants.h"
#include "utility.h"
#include "Gate.h"

int FLAG_ABORT_PENDING = 0;
int FLAG_SEQUENCE_RUNNING = 0;
int FLAG_IS_ABORTABLE = 0;

Gate::Gate(){
  Gate::ready();
}

void Gate::random_wait() {
  int rand_delay = random(DELAY_RAND_MIN,DELAY_RAND_MAX+1);
  unsigned long wait_timer = millis() + rand_delay;
  serial_print_val("Gate sequence random wait time",rand_delay);
  while((millis() < wait_timer) && (!FLAG_ABORT_PENDING)) {
    // waiting for random wait to finish
    delayMicroseconds(100); // prevent blocking
  }
  serial_print("Wait timer done");
}

void Gate::ready(){
  FLAG_ABORT_PENDING = 0;
  FLAG_IS_ABORTABLE = 0;
}

void Gate::arm() {
  // turn on magnet
  digitalWrite(PIN_RELAY, HIGH); // turn on magnet
  serial_print("Magnet powered");
}

void Gate::abort() {
  FLAG_ABORT_PENDING = 1;
}

void Gate::drop() {
  digitalWrite(PIN_RELAY, LOW);
  serial_print("Magnet released");
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
