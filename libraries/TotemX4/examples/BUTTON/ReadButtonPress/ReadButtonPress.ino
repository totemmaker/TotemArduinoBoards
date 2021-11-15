#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example displaying button usage
           When button is pressed - LED will turn off
           When button is double clicked - LED will blink
           When button is held down 1s - RGB LED will blink
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Check if button was double clicked
  if (X4.button.wasDoubleClick()) {
    X4.led.blink(); // Blink LED
  }
  // Check if button is currently pressed
  else if (X4.button.isPressed()) {
    X4.led.off(); // Turn LED off
    // Loop while button is held in
    while (X4.button.isPressed()) {
      // Loop if button is pressed for 1s or longer
      while (X4.button.isPressedFor(1000)) { 
        // Toggle RGB LED every 50ms
        X4.rgb.toggle();
        delay(50);
      }
      delay(1); // Just to prevent blocking CPU core
    }
    // Turn LED back on
    X4.led.on();
  }
}