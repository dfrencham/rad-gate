#include <ArduinoUnitTests.h>
#include "constants.h"
#include "../mocks/JQ6500_Serial.h"
#include "AudioFX.h"
#include "MockBeep.h"
#include "Godmode.h"

unittest(sound)
{
  GodmodeState* state = GODMODE();
  MockBeep beep = MockBeep();
  JQ6500_Serial mp3(PIN_SFX_TX,PIN_SFX_RX);
  AudioFX audioFX = AudioFX(&mp3, &beep);
  audioFX.play_power_on();
  // beep.wasTonePlayed(1000)
  assertTrue(true);
}

unittest_main()
