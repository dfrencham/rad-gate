/*****************************************
 *  utility.ino 
 *  (c) Danny Frencham 2017
 *****************************************/

// Prints a string to serial
//  print_string    string to print
void serial_print(const char* print_string) {
  if (Serial) {
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print(print_string);
    Serial.print("\n");
  }
}

// Prints a named value to serial
//  print_string    description
//  print_val       value
void serial_print_val(const char* print_string, unsigned long print_val) {
    if (Serial) {
          Serial.print("[");
          Serial.print(millis());
          Serial.print("] ");
          Serial.print(print_string);
          Serial.print(" ");
          Serial.print(print_val);
          Serial.print("\n");
    }
}

// LED light chase
//  c               colour
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(50);
  }
}
