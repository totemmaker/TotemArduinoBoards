#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  Details: Example showing inverted functionality of LED position display.
           All LED are on except LED at line position
  
  Note: By default 8 on-board LED displays position of line.
  This functionality can be disabled when some custom action is set
  to sensor.led. Use sensor.led.reset() to restore default functionality
  during runtime.
*/
// Initialize Line Follower
Module14 sensor;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Convert position to led channel
  int ledCh = map(sensor.line.getPosition(), -35, 35, chA, chH);
  // Prepare binary value with single LED enabled
  // Each bit represents LED state (1 - on, 0 - off)
  // B00000000 <- 8-bit value
  //  HGFEDCBA <- LED name
  // Example: (chF)(5) -> B00100000. Turns LED F on.
  uint8_t binary = BIT(ledCh);
  // Now invert 8-bit value to turn off selected LED and on all others.
  // B00100000 -> B11011111
  // Send inverted binary value to module
  sensor.led.setBinary(~binary);
}