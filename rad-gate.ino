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

#ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
  SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
  Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
  AudioFX audio = AudioFX(&sfx);
#endif
#ifdef HARDWARE_SOUNDBOARD_JQ6500
  JQ6500_Serial mp3(SFX_TX,SFX_RX);
  AudioFXaudio = AudioFX(&mp3);
#endif

LightTree lighttree = LightTree(PIN_NEO_PIXEL);
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
  
  #ifdef HARDWARE_SOUNDBOARD_ADAFRUIT
    ss.begin(9600);
  #endif
  #ifdef HARDWARE_SOUNDBOARD_JQ6500
    mp3.begin(9600);
    mp3.reset();
  #endif

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

  lighttree.ready();
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
      //sfx.playTrack(SFX_PREP);
      //audio.play_sound_samples();
    } // else still holding button
  }
}
