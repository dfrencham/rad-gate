#include <ArduinoUnitTests.h>
#include "constants.h"
#include "Sequence.h"
#include "Gate.h"
#include "LightTree.h"
#include "AudioFX.h"
#include "Godmode.h"

unittest(gate_ready)
{
  GodmodeState* state = GODMODE();
  Gate gate = Gate();
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

unittest_main();
