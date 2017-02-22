/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

#include <SoftwareSerial.h>
#include "constants.h"
#include "utility.h"
#include "AudioFX.h"
#include "LightTree.h"
#include "Gate.h"
#include "Sequence.h"

// declarations
bool buttonPressed = 0;
LightTree lighttree = LightTree(PIN_NEO_PIXEL);
AudioFX audio = AudioFX();
Gate gate = Gate();
Sequence sequence = Sequence(&gate,&audio,&lighttree);

// interrrupt handler
void Interrupt1()
{
  if (gate.is_abortable() && !gate.is_aborted()) {
    serial_print("Interrupt triggered");
    gate.abort();
  }
  else {
    serial_print("Interrupt ignored");
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_ACTIVE, OUTPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_BUTTON_GO, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(SFX_ACT, INPUT);
  //pinMode(PIN_REED_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(1), Interrupt1, RISING);
  digitalWrite(3, HIGH); // interrupt on 3
  digitalWrite(PIN_RELAY, LOW); // turn on magnet

  Serial.begin(115200);
  serial_print("Gate controller initialised");
  serial_print(VERSION);
}

void loop() {
  if (digitalRead(PIN_BUTTON_GO) == LOW) {
    buttonPressed = 0; // reset
  }
  else if (digitalRead(PIN_BUTTON_GO) == HIGH)
  {
    if (gate.is_sequence_running()) {
      gate.abort();
    }
    // only fire the button press action once
    if (!buttonPressed) {
      buttonPressed = 1;
      sequence.begin_sequence();
    } // else still holding button
  }
}
