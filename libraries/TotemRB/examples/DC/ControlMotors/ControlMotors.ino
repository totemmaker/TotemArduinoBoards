#include <Arduino.h>
/*
  RoboBoard example to control DC motor output.
  Press button to switch to next example after it completes.
  Current stage of example is indicated by RGB LED
*/
// Initialize program
void setup() {
  // Empty
}
// Motor power output control
void example1() {
  DC.spin(10); // Spin at 10% power
  delay(2000);
  DC.spin(50); // Spin at 50% power
  delay(2000);
  DC.spin(100); // Spin at 100% power
  delay(1000);
  DC.brake();   // Stop spin with brake
  delay(1000);
}
// Motor brake control
void example2() {
  DC.spin(100); // Spin at 100% power
  delay(2000);
  DC.brake(100); // Brake at 100% power
  delay(1000);
  DC.spin(100); // Spin at 100% power
  delay(2000);
  DC.brake(30); // Brake at 30% power
  delay(1000);
  DC.spin(100); // Spin at 100% power
  delay(2000);
  DC.coast(); // Free spin
  delay(1000);
}
// Motor changing direction
void example3() {
  DC.spin(50); // Spin at 50% power
  delay(2000);
  DC.spin(-50); // Spin backwards at 50% power
  delay(2000);
  DC.setInvert(true); // Invert spin direction
  delay(1000);
  DC.setInvert(false); // Restore default spin direction
  delay(1000);
  DC.brake();   // Stop spin with brake
  delay(1000);
}
// Motor automatic braking
void example4() {
  // 100% autobrake
  DC.spin(80); // Spin at 80% power
  DC.setAutobrake(true); // Enable autobrake at 100%
  delay(2000);
  DC.spin(0); // Set power to 0%. Motor will brake
  delay(1000);
  // Disabled autobrake
  DC.spin(80); // Spin at 80% power
  DC.setAutobrake(false); // Disable autobrake
  delay(1000);
  DC.spin(0); // Set power to 0%. Motor slow down on it's own
  delay(2000);
}
// Loop program
void loop() {
  // Example 1: Motor power output control
  RGB.off(); RGB.A.color(Color::Green); // Turn LED A
  while (!Button.wasPressed()) { example1(); }
  // Example 2: Motor brake control
  RGB.off(); RGB.B.color(Color::Green); // Turn LED B
  while (!Button.wasPressed()) { example2(); }
  // Example 3: Motor changing direction
  RGB.off(); RGB.C.color(Color::Green); // Turn LED C
  while (!Button.wasPressed()) { example3(); }
  // Example 4: Motor automatic braking
  RGB.off(); RGB.D.color(Color::Green); // Turn LED D
  while (!Button.wasPressed()) { example4(); }
}