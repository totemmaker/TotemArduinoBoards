#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  RoboBoard example to read knob value and update LED with custom actions.
  Turn knob to change LED blinking speed.
  This example also demonstrates multithreading with "addLoop".
  
  Note: By default 3 on-board LED displays position of knob.
  This functionality is disabled when some custom action is set
  to pot.led. Use pot.led.reset() to restore default functionality.
*/
// Initialize Potentiometer module
TotemModule15 pot;
// Create separate loop for LED A
void loopLEDA() {
  pot.led[0].toggle(); // Toggle LED A
  int knob = pot.getKnobA(); // Read knobA
  // Delay amount of time depending on knob position
  // Prevent setting delay to 0 because it takes all 
  // module bandwidth, slowing down other tasks
  if (knob == 0) knob = 1;
  delay(knob);
}
// Create separate loop for LED B
void loopLEDB() {
  pot.led[1].toggle(); // Toggle LED B
  int knob = pot.getKnobB(); // Read knobB
  // Delay amount of time depending on knob position
  if (knob == 0) knob = 1;
  delay(knob);
}
// Create separate loop for LED C
void loopLEDC() {
  pot.led[2].toggle(); // Toggle LED C
  int knob = pot.getKnobC(); // Read knobC
  // Delay amount of time depending on knob position
  if (knob == 0) knob = 1;
  delay(knob);
}
// Initialize program
void setup() {
  // Create parallel loop tasks for each LED
  // Each function acts same as independent loop()
  addLoop(loopLEDA);
  addLoop(loopLEDB);
  addLoop(loopLEDC);
}
// Loop program
void loop() {
  // Do nothing
  delay(1);
}