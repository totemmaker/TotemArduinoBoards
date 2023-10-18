#include <Arduino.h>
/*
  RoboBoard example to interact with RGB light bar
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Set to Totem colors (green, yellow, yellow, blue)
  RGB.colorTotem();
  delay(1000);
  // Set to RED color
  RGB.color(255, 0, 0); // red, green, blue
  delay(1000);
  // Set to GREEN color
  RGB.color(0, 255, 0); // red, green, blue
  delay(1000);
  // Set to BLUE color
  RGB.color(0, 0, 255); // red, green, blue
  delay(1000);
  // Set to HEX value to violet color (#EE82EE) 
  RGB.color(0xEE82EE); // HEX [0:0xFFFFFF] color code
  delay(1000);
  // Set cyan color (name)
  RGB.color(Color::Cyan);
  delay(1000);
  // Control each LED differently
  RGB.A.color(Color::Red); // Set RGB A to RED
  RGB.B.color(Color::Green); // Set RGB B to GREEN
  RGB.C.color(Color::Blue); // Set RGB C to BLUE
  RGB.D.color(Color::White); // Set RGB D to WHITE
  delay(1000);
}
