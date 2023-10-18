#include <Arduino.h>
/*
  RoboBoard example to interact with status LED.
  Note: RoboBoard X3 LED is emulated with RGB A.
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Turn on
  LED.on();
  delay(1000);
  // Turn off
  LED.off();
  delay(1000);
  // Blink 5 times
  LED.blink(5);
  LED.wait(); // Wait until blink stops
}
