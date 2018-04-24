#include <ArduinoUnitTests.h>
#include "constants.h"
#include "../mocks/Adafruit_NeoPixel.h"
#include "LightTree.h"
#include "Gate.h"
#include "Godmode.h"
#include "mockConstants.h"

unittest(lighttree)
{
  cerr << "  LightTree test" << endl;
  GodmodeState* state = GODMODE();
  LightTree lt = LightTree();
  Gate gate = Gate();

  lt.initialise(false,1);
  lt.ready();
  Adafruit_NeoPixel strip = lt.getStrip();

  assertTrue(strip.wasPixelLit(1));

  lt.light_set(1,&gate);
  assertTrue(strip.wasPixelLit(6));
  assertTrue(strip.wasPixelLit(7));

  lt.light_set(2,&gate);
  assertTrue(strip.wasPixelLit(4));
  assertTrue(strip.wasPixelLit(5));

  lt.light_set(3,&gate);
  assertTrue(strip.wasPixelLit(3));
  assertTrue(strip.wasPixelLit(2));

  lt.light_set(4,&gate);
  assertTrue(strip.wasPixelLit(1));
  assertTrue(strip.wasPixelLit(0));
}

unittest(lighttree_use_relays)
{
  cerr << "  LightTree relay test" << endl;
  GodmodeState* state = GODMODE();
  LightTree lt = LightTree();
  Gate gate = Gate();

  lt.initialise(true,1);
  lt.ready();

  lt.light_set(1,&gate);
  assertEqual(LOW, state->digitalPin[PIN_LIGHT_TREE_RELAY_1]);

  lt.light_set(2,&gate);
  assertEqual(LOW, state->digitalPin[PIN_LIGHT_TREE_RELAY_2]);

  lt.light_set(3,&gate);
  assertEqual(LOW, state->digitalPin[PIN_LIGHT_TREE_RELAY_3]);

  lt.light_set(4,&gate);
  assertEqual(LOW, state->digitalPin[PIN_LIGHT_TREE_RELAY_4]);
}

unittest_main();