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
  X4.rgb.fadeColorHEX(chAll, 0x6C3483); // RGB color HEX
  // Start animation for 3 seconds duration
  X4.rgb.fadeStart(chAll, 3000);
  delay(4000); // Wait for animation to finish
  /*
    Set individual LED color
  */
  X4.rgb.fadeColorRGB(chA, 255, 255, 255);
  X4.rgb.fadeColorRGB(chB, 0, 0, 255);
  X4.rgb.fadeColorRGB(chC, 0, 255, 0);
  X4.rgb.fadeColorRGB(chD, 255, 0, 0);
  X4.rgb.fadeStart(chAll, 3000);
  delay(4000);
  /*
    Set individual LED animation
  */
  X4.rgb.fadeColorTotem();
  X4.rgb.fadeStart(chA, 500);
  X4.rgb.fadeStart(chB, 1000);
  X4.rgb.fadeStart(chC, 1500);
  X4.rgb.fadeStart(chD, 2000);
  delay(3000);
}