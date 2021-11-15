#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  Details: Example showing how to control LED
  
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
  // Play some LED animations
  /*
    Loading
  */
  sensor.led.off();
  for (int c=0; c<2; c++) {
    for (int i=0; i<8; i++) {
      sensor.led.onX(i); // Turn on single LED (A, B, C...)
      delay(50);
    }
    for (int i=0; i<8; i++) {
      sensor.led.offX(i); // Turn off single LED (A, B, C...)
      delay(50);
    }
    for (int i=7; i>=0; i--) {
      sensor.led.onX(i); // Turn on single LED (A, B, C...)
      delay(50);
    }
    for (int i=7; i>=0; i--) {
      sensor.led.offX(i); // Turn off single LED (A, B, C...)
      delay(50);
    }
  }
  /*
    Binary count
  */
  for (int c=0; c<32; c++) {
    sensor.led.setBinary(c); // Output binary value B101... -> A:on, B:off, C:on...
    delay(500);
  }
  /*
    Blink
  */
  for (int c=0; c<10; c++) {
    sensor.led.toggle(); // Toggle all LED (on / off)
    delay(100);
  }
}