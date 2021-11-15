#include <Arduino.h>
/*
  Module:  [22] Totem Environment sensor module
  Details: Example showing how to control LED
*/
// Initialize Environment sensor module
Module22 sensor;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Play some LED animations
  /*
    Pulse blinking
  */
  for (int t=10; t<200; t+=10) {
    sensor.led.toggle();
    delay(t);
  }
  for (int t=200; t>=10; t-=10) {
    sensor.led.toggle();
    delay(t);
  }
}