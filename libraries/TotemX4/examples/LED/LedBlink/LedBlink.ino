#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to interact with on board LED
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Turn on
  X4.led.on();
  delay(2000);
  // Turn off
  X4.led.off();
  delay(2000);
  // Toggle on / off
  X4.led.toggle();
  delay(500);
  X4.led.toggle();
  delay(500);
  // Set state on
  X4.led.set(HIGH); // accepted params: 1, true, HIGH
  delay(2000);
  // Turn off
  X4.led.set(LOW); // accepted params: 0, false, LOW
  delay(2000);
  // Blink once
  X4.led.blink();
  delay(2000);
  // Blink 5 number of times
  X4.led.blinkTimes(5);
  delay(2000);
  // Blink for 2 seconds
  X4.led.blinkFor(2000);
  delay(3000);
  /*
    Pulse blinking
  */
  for (int t=10; t<200; t+=10) {
    X4.led.toggle();
    delay(t);
  }
  for (int t=200; t>=10; t-=10) {
    X4.led.toggle();
    delay(t);
  }
}