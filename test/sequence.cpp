#include <ArduinoUnitTests.h>
#include "constants.h"
#include "Sequence.h"
#include "Gate.h"
#include "LightTree.h"
#include "MockBeep.h"
#include "AudioFX.h"
#include "Godmode.h"
#include "../mocks/JQ6500_Serial.h"
#include "unistd.h"

unittest(gate_ready)
{
  GodmodeState* state = GODMODE();
  Gate gate = Gate();
  //LightTree lighttree = LightTree();
  //Sequence sequence = Sequence(&gate,&audioFX,&lighttree);

  //sequence.begin_sequence();
  
  gate.ready();
  assertFalse(gate.is_sequence_running());
}

unittest(gate_drops)
{
  GodmodeState* state = GODMODE();
  Gate gate = Gate();
  gate.ready();
  
  gate.drop();
  assertEqual(LOW, state->digitalPin[PIN_RELAY]);
  assertFalse(gate.is_sequence_running());

  // clean up
  gate.set_sequence_running(false);
}

unittest(gate_abort)
{
  GodmodeState* state = GODMODE();
  Gate gate = Gate();
  gate.ready();
  
  assertEqual(false, gate.is_abortable());
  
  gate.set_sequence_running(true);
  assertEqual(true, gate.is_abortable());
  assertEqual(true, gate.is_sequence_running());

  gate.abort();
  assertEqual(false, gate.is_abortable());

  // clean up
  gate.set_sequence_running(false);
}

unittest(sequence)
{
  GodmodeState* state = GODMODE();
  state->reset(); 

  Gate gate = Gate();
  //gate.ready();

  LightTree lighttree = LightTree();
  MockBeep mbeep = MockBeep();
  JQ6500_Serial mp3(PIN_SFX_TX,PIN_SFX_RX);
  AudioFX audioFX = AudioFX(&mp3, &mbeep);

  assertEqual(LOW, state->digitalPin[PIN_RELAY]);
  gate.arm();
  assertEqual(HIGH, state->digitalPin[PIN_RELAY]);

  Sequence sequence = Sequence(&gate,&audioFX,&lighttree);

  sequence.begin_sequence();
  
  //gate.ready();

  assertFalse(gate.is_sequence_running());
  assertEqual(4, state->digitalPin[PIN_RELAY].historySize());

  bool expected[4] = {LOW, HIGH, LOW, HIGH};
  bool actual[4];
  state->digitalPin[PIN_RELAY].toArray(actual,3);

  for (int i = 0; i < 3; ++i) {
    assertEqual(expected[i], actual[i]);
  }

  // state->digitalPin[1].fromArray
  // assertEqual(6, state->digitalPin[1].size());

}


unittest_main()