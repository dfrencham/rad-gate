#include <ArduinoUnitTests.h>
#include "constants.h"
#include "../mocks/JQ6500_Serial.h"
#include "AudioFX.h"
#include "MockBeep.h"
#include "Godmode.h"

unittest(sound)
{
  cerr << "  Sound test" << endl;
  GodmodeState* state = GODMODE();
  MockBeep mbeep = MockBeep();
  JQ6500_Serial mp3(PIN_SFX_TX,PIN_SFX_RX);
  AudioFX audioFX = AudioFX(&mp3, &mbeep);
  audioFX.play_power_on();
  assertTrue(mbeep.wasTonePlayed(1000));
  assertTrue(mbeep.wasTonePlayed(1333));
}

unittest_main()
