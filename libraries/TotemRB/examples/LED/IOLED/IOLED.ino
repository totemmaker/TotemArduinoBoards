#include <Arduino.h>
/*
  RoboBoard example to interact with external LED.
*/
#if ROBOBOARD_X3
IOLED led(IO33);
#endif
#if ROBOBOARD_X4
IOLED led(GPIOA);
#endif
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Turn on
  led.on();
  delay(1000);
  // Turn off
  led.off();
  delay(1000);
  // Blink 5 times
  led.blink(5);
  led.wait(); // Wait until blink stops
}