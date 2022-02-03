#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to control DC motor output
           Press button to switch to next example after it completes.
           Current number of example is indicated by RGB LED
*/
// Initialize program
void setup() {
  // Empty
}
// Motor power output control
void example1() {
  X4.dc.power(chA, 10); // Spin at 10% power
  delay(2000);
  X4.dc.power(chA, 50); // Spin at 50% power
  delay(2000);
  X4.dc.power(chA, 100); // Spin at 100% power
  delay(1000);
  X4.dc.brake(chA);   // Stop spin with brake
  delay(1000);
}
// Motor brake control
void example2() {
  X4.dc.power(chA, 50); // Spin at 50% power
  delay(2000);
  X4.dc.brake(chA, 100); // Brake at 100% power
  delay(1000);
  X4.dc.power(chA, 50); // Spin at 50% power
  delay(2000);
  X4.dc.brake(chA, 50); // Brake at 50% power
  delay(1000);
}
// Motor changing direction
void example3() {
  X4.dc.power(chA, 50); // Spin at 50% power
  delay(2000);
  X4.dc.power(chA, -50); // Spin backwards at 50% power
  delay(2000);
  X4.dc.setInvert(chA, true); // Invert spin direction
  delay(1000);
  X4.dc.setInvert(chA, false); // Restore default spin direction
  delay(1000);
  X4.dc.brake(chA);   // Stop spin with brake
  delay(1000);
}
// Motor automatic braking
void example4() {
  // 100% autobrake example
  X4.dc.power(chA, 50); // Spin at 50% power
  X4.dc.setAutobrake(chA, true); // Enable autobrake at 100%. Same as X4.dc.setAutobrake(chA, 100)
  delay(2000);
  X4.dc.power(chA, 0); // Set power to 0%. Motor will brake
  delay(1000);
  // Disabled autobrake example
  X4.dc.power(chA, 50); // Spin at 50% power
  X4.dc.setAutobrake(chA, false); // Disable autobrake. Same as X4.dc.setAutobrake(chA, 0)
  delay(1000);
  X4.dc.power(chA, 0); // Set power to 0%. Motor slow down on it's own
  delay(2000);
}
// Loop program
void loop() {
  // Example 1: Motor power output control
  X4.rgb.off(chAll); X4.rgb.colorRGB(chA, 0, 255, 0); // Turn LED A
  while (!X4.button.wasPressed()) { example1(); }
  // Example 2: Motor brake control
  X4.rgb.off(chAll); X4.rgb.colorRGB(chB, 0, 255, 0); // Turn LED B
  while (!X4.button.wasPressed()) { example2(); }
  // Example 3: Motor changing direction
  X4.rgb.off(chAll); X4.rgb.colorRGB(chC, 0, 255, 0); // Turn LED C
  while (!X4.button.wasPressed()) { example3(); }
  // Example 4: Motor automatic braking
  X4.rgb.off(chAll); X4.rgb.colorRGB(chD, 0, 255, 0); // Turn LED D
  while (!X4.button.wasPressed()) { example4(); }
}