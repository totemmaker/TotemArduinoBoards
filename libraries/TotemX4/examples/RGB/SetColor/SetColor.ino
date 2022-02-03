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
  X4.rgb.colorARGB(chAll, 50, 255, 0, 0); // brightness, red, green, blue
  delay(1000);
  // Set to GREEN color to 100% brightness
  // Each parameter is value between [0:255]
  X4.rgb.colorRGB(chAll, 0, 255, 0); // red, green, blue
  delay(1000);
  // Set to violet color (#6C3483) at 179 -> 70% brightness
  X4.rgb.colorAHEX(chAll, 179, 0x6C3483); // brightness, HEX [0:0xFFFFFF] RGB
  delay(1000);
  // Set to violet color (#6C3483) at 0xFF -> 100% brightness
  X4.rgb.colorHEX(chAll, 0x6C3483); // HEX [0:0xFFFFFF] RGB
  delay(1000);
  // Set to "Orange" color (#FFA500). Predefined list of Color::name can be used
  // Examples: Color::Red, Color::Yellow, Color::DarkOrchid, Color::Purple
  X4.rgb.colorHEX(chAll, Color::Orange); // HEX [0:0xFFFFFF] (color name)
  delay(2000);
  // Turn off
  X4.rgb.off(chAll);
  delay(500);
  // Turn on
  X4.rgb.on(chAll);
  delay(500);
  // Blink using toggle function
  for (int c=0; c<15; c++) {
    X4.rgb.toggle(chAll); // Toggle (on / off)
    delay(100);
  }
   // Set state on
  X4.rgb.set(chAll, HIGH); // accepted params: 1, true, HIGH
  delay(1000);
  // Turn off
  X4.rgb.set(chAll, LOW); // accepted params: 0, false, LOW
  delay(1000);
  // Control each LED differently
  X4.rgb.colorRGB(chA, 255, 0, 0); // Set RGB A to RED
  X4.rgb.colorRGB(chB, 0, 255, 0); // Set RGB B to GREEN
  X4.rgb.colorRGB(chC, 0, 0, 255); // Set RGB C to BLUE
  X4.rgb.colorRGB(chD, 255, 255, 255); // Set RGB D to WHITE
  delay(2000);
}