#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to play RGB fade animations
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  /*
    Animate ALL LED
  */
  // Prepare violet color for animation
  X4.rgb.fadeColor(255, 0x6C3483); // brightness | RGB color HEX
  // Start animation for 3 seconds duration
  X4.rgb.fadeStart(3000);
  delay(4000); // Wait for animation to finish
  /*
    Set individual LED color
  */
  X4.rgbA.fadeColor(255, 255, 255);
  X4.rgbB.fadeColor(0, 0, 255);
  X4.rgbC.fadeColor(0, 255, 0);
  X4.rgbD.fadeColor(255, 0, 0);
  X4.rgb.fadeStart(3000);
  delay(4000);
  /*
    Set individual LED animation
  */
  X4.rgb.fadeColorTotem();
  X4.rgbA.fadeStart(500);
  X4.rgbB.fadeStart(1000);
  X4.rgbC.fadeStart(1500);
  X4.rgbD.fadeStart(2000);
  delay(3000);
}