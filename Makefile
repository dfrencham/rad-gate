# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

MONITOR_PORT  = /dev/cu.wchusbserial1420
BOARD_TAG     = uno
ARDUINO_LIBS = SoftwareSerial Adafruit_NeoPixel JQ6500_Serial Adafruit_Soundboard_library
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Java
ARDMK_DIR     = /usr/local/opt/arduino-mk
AVR_TOOLS_DIR = /Applications/Arduino.app/Contents/Java/hardware/tools/avr
USER_LIB_PATH = $(realpath ../libraries)

# Last
include $(ARDMK_DIR)/Arduino.mk
