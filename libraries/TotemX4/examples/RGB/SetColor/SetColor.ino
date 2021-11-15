#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to interact with RGB LED
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Set to Totem colors
  X4.rgb.colorTotem();
  delay(1000);
  /*
    Setting color to RGB LED can be done using
    multiple of convinient functions
  */
  // Set to RED color with 50 -> 19.6% brightness
  // Each parameter is value between [0:255]
  X4.rgb.color(50, 255, 0, 0); // brightness, red, green, blue
  delay(1000);
  // Set to GREEN color to 100% brightness
  // Each parameter is value between [0:255]
  X4.rgb.color(0, 255, 0); // red, green, blue
  delay(1000);
  // Set to violet color (#6C3483) at 179 -> 70% brightness
  X4.rgb.color(179, 0x6C3483); // brightness, HEX [0:0xFFFFFF] RGB
  delay(1000);
  // Set to violet color (#6C3483) at 0xFF -> 100% brightness
  // HEX includes brightness
  X4.rgb.color(0xFF6C3483); // HEX [0:0xFFFFFFFF] brightness|RGB
  delay(2000);
  // Turn off
  X4.rgb.off();
  delay(500);
  // Turn on
  X4.rgb.on();
  delay(500);
  // Blink using toggle function
  for (int c=0; c<15; c++) {
    X4.rgb.toggle(); // Toggle (on / off)
    delay(100);
  }
   // Set state on
  X4.rgb.set(HIGH); // accepted params: 1, true, HIGH
  delay(1000);
  // Turn off
  X4.rgb.set(LOW); // accepted params: 0, false, LOW
  delay(1000);
  // Control each LED differently
  X4.rgbA.color(255, 0, 0); // Set RGB A to RED
  X4.rgbB.color(0, 255, 0); // Set RGB B to GREEN
  X4.rgbC.color(0, 0, 255); // Set RGB C to BLUE
  X4.rgbD.color(255, 255, 255); // Set RGB D to WHITE
  delay(2000);
}