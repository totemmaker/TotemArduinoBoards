#include <Arduino.h>
/*
  Board:  [X3] RoboBoard X3
  RoboBoard example to interact with GPIO pins.
*/
#if !ROBOBOARD_X4
#error "This example only works with RoboBoard X4"
#endif
// Initialize program
void setup() {
  // Use standard Arduino API to interact with GPIO pins
  pinMode(IO26, INPUT_PULLDOWN);  // Set IO26 to INPUT with pulling to LOW
  pinMode(IO32, OUTPUT); // Set IO32 to OUTPUT
  pinMode(IO33, OUTPUT); // Set IO33 to OUTPUT
}
// Loop program
void loop() {
  digitalWrite(IO32, HIGH); // Set IO32 to HIGH (3.3 Volts -> VCC)
  digitalWrite(IO33, LOW); // Set IO33 to LOW (0 Volts -> GND)
  delay(1000); // Wait 1 second
  digitalWrite(IO32, LOW); // Set IO32 to LOW (0 Volts -> GND)
  digitalWrite(IO33, HIGH); // Set IO33 to HIGH (3.3 Volts -> VCC)
  delay(1000); // Wait 1 second
  if (digitalRead(IO26)) { // Turn green color if IO26 == HIGH
    RGB.color(Color::Green);
  }
  else { // Turn red color if IO26 == LOW
    RGB.color(Color::Red);
  }
}