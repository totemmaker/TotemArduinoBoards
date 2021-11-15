#include <Arduino.h>
/*
  Module:  [14] Line Follower module
           [15] Potentiometer module
  Details: Example displaying control of two distinct modules at the same time.
           Turning Knob A will change LED on Line Follower module
           Turning Knob B will change X4 RGB brightness
           Turning Knob C will change X4 RGB color
*/
// Initialize Line Follower module
Module14 line;
// Initialize Potentiometer module
Module15 pot;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Receive knob positions
  int knobA = pot.knobA.get();
  int knobB = pot.knobB.get();
  int knobC = pot.knobC.get();
  // Set Line Follower LED
  line.led.off();
  line.led.onX(
    map(knobA, 0, 255, 0, 7) // map [0:255] -> [0:7]
  );
  // Set X4 RGB LED
  X4.rgb.color(
    knobB, knobC, 255-knobC, 0 // alpha, reg, green, blue
  );
  // Delay 20 milliseconds
  delay(20);
}