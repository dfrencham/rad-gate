# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

MONITOR_PORT  = /dev/ttyACM0
#MONITOR_PORT = /dev/cu.wchusbserial1420
BOARD_TAG     = uno
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Java
ARDMK_DIR     = /usr/local/opt/arduino-mk
AVR_TOOLS_DIR = /Applications/Arduino.app/Contents/Java/hardware/tools/avr
USER_LIB_PATH = $(realpath libs)

# Last
include $(ARDMK_DIR)/Arduino.mk
