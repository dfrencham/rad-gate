/*****************************************
 *  RemoteArDuino (RAD) Gate
 *  (c) Danny Frencham 2017
 *****************************************/

 /********************************************
 *  Notes: 
 *  To use relays for light control, ground
 *  pin 3.
 *  Relays should be connected to A0,A1,A2,A3
 *********************************************/

#include <SoftwareSerial.h>
#include "constants.h"
#include "utility.h"
#include "AudioFX.h"
#include "LightTree.h"
#include "Gate.h"
#include "Sequence.h"
#include <JQ6500_Serial.h>

// declarations
bool buttonPressed = 0;

#ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
  SoftwareSerial ss = SoftwareSerial(PIN_SFX_TX, PIN_SFX_RX);
  Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, PIN_SFX_RST);
  AudioFX audioFX = AudioFX(&sfx);
#endif
#ifdef HARDWARE_SOUNDBOARD_JQ6500
  JQ6500_Serial mp3(PIN_SFX_TX,PIN_SFX_RX);
  AudioFX audioFX = AudioFX(&mp3);
#endif

Gate gate = Gate();
LightTree lighttree = LightTree();
Sequence sequence = Sequence(&gate,&audioFX,&lighttree);

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

  Serial.begin(19200);

  #ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
    ss.begin(9600);
    pinMode(PIN_SFX_ACT, INPUT);
    serial_print("Adafruit Sound board initialised");
  #endif
  #ifdef HARDWARE_SOUNDBOARD_JQ6500
    mp3.begin(9600);
    mp3.reset();
    mp3.setVolume(25);
    mp3.setLoopMode(MP3_LOOP_NONE);
    serial_print("JQ6500 initialised");
  #endif

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_ACTIVE, OUTPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_BUTTON_GO, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  //pinMode(PIN_REED_SWITCH, INPUT_PULLUP);
  pinMode(PIN_LIGHT_TREE_RELAY_ENABLE, INPUT_PULLUP);

  // not working? not needed?
  //attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_GO), Interrupt1, HIGH);
  digitalWrite(PIN_RELAY, HIGH); // turn on magnet

  if (digitalRead(PIN_LIGHT_TREE_RELAY_ENABLE) == LOW) {
    lighttree.initialise(true, PIN_LIGHT_TREE_RELAY_ENABLE);
    serial_print("Light tree configured for relay control");
  } else {
    lighttree.initialise(false, PIN_NEO_PIXEL);
    serial_print("Light tree configured for serial control");
  }

  serial_print("Gate controller initialised");
  serial_print(VERSION);
  delay(100);
  lighttree.led_reset();
  lighttree.ready();
  audioFX.play_power_on();
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
