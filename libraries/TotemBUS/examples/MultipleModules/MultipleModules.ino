#include <Arduino.h>
/*
  Module:  [14] Line Follower module
           [15] Potentiometer module
  RoboBoard example to control two distinct modules at the same time.
  Turning Knob A will change LED on Line Follower module.
  Turning Knob B will change X4 RGB brightness.
  Turning Knob C will change X4 RGB color.
*/
// Initialize Line Follower module
TotemModule14 line;
// Initialize Potentiometer module
TotemModule15 pot;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Receive knob positions
  int knobA = pot.getKnobA();
  int knobB = pot.getKnobB();
  int knobC = pot.getKnobC();
  // Set Line Follower LED
  line.led.off();
  line.led[map(knobA, 0, 255, 0, 7)].on(); // map [0:255] -> [0:7]
  // Set X4 RGB LED
  RGB.color(
    255-knobB, knobC, 255-knobC // reg, green, blue
  );
  // Delay 20 milliseconds
  delay(20);
}