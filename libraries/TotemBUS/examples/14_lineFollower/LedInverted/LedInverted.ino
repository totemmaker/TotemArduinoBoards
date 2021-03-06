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
  // Convert position to led number (index)
  int led = map(sensor.pos.get(), -35, 35, 0, 7);
  // Prepare LED array binary with single LED enabled
  // Need to substract from 7 to change direction
  // Example: 5 -> B00000100 (led index starts at 0 (0-7))
  led = 5;
  uint8_t binary = BIT(7-led);
  // Set binary to module. Invert all 0->1 and 0->1
  // to light up all LED and turn off selected one
  sensor.led.setBinary(~binary);
}