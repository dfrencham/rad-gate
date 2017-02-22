### RAD Gate ###
## RemoteArDuino BMX Gate Controller ##

This project is an Open Source gate controller for BMX gates. You will need to build the controller yourself.

# Features

- spoken cadence
- random start
- remote control
- light tree
- Conforms to BMX Australia / UCI gate cadence

# Requirements

- Arduino based micro controller with 11 digital IO pins
  - This design has been proven to run on the Arduino Uno (both the Adafruit Metro, and Robotdyne Uno clones)
  - It also runs on the ESP8266, but you may need to change some of the pin references
- Soundboard, I recommend the JQ2500 model. The Adafruit SoundFX boards also work
- Amplifier module
- Electro magnetic latch
- (optional for light tree) NeoPixel stick (Adafruit or Banggood clone)
- (optional for remote control) remote module
  - any remote module will work, as long as it can trigger a signal on one of the input pins

# Build

This project can be built using the Arduino IDE, or on the command line:

````
user@host$ make
````

# Schematic

Coming soon
