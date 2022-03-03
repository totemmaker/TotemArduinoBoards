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
  int knobA = pot.knob.getPosition(chA);
  int knobB = pot.knob.getPosition(chB);
  int knobC = pot.knob.getPosition(chC);
  // Set Line Follower LED
  line.led.off(chAll);
  line.led.on(
    map(knobA, 0, 255, chA, chH) // map [0:255] -> [0:7]
  );
  // Set X4 RGB LED
  X4.rgb.colorARGB(chAll,
    knobB, knobC, 255-knobC, 0 // alpha, reg, green, blue
  );
  // Delay 20 milliseconds
  delay(20);
}