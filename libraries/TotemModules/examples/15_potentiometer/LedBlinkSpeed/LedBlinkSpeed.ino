#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  Details: Example showing how to read knob value and update LED
           with custom actions. Turn knob to change LED blinking speed.
           This example also demonstrates multithreading with "addLoop"
  
  Note: By default 3 on-board LED displays position of knob.
  This functionality can be disabled when some custom action is set
  to pot.led. Use pot.led.reset() to restore default functionality
  during runtime.
*/
// Initialize Potentiometer module
Module15 pot;
// Create separate loop for LED A
void loopLEDA() {
  pot.led.toggleX(0); // Toggle LED A
  int knob = pot.knobA.get(); // Read knobA
  // Delay amount of time depending on knob position
  // Avoid setting delay to 0 because it takes all 
  // module bandwidth, slowing down other tasks
  delay(knob == 0 ? 1 : knob);
}
// Create separate loop for LED B
void loopLEDB() {
  pot.led.toggleX(1); // Toggle LED B
  int knob = pot.knobB.get(); // Read knobB
  // Delay amount of time depending on knob position
  delay(knob == 0 ? 1 : knob);
}
// Create separate loop for LED C
void loopLEDC() {
  pot.led.toggleX(2); // Toggle LED C
  int knob = pot.knobC.get(); // Read knobC
  // Delay amount of time depending on knob position
  delay(knob == 0 ? 1 : knob);
}
// Initialize program
void setup() {
  // Create parallel loop tasks for each LED
  // Each function acts same as independend loop()
  addLoop(loopLEDA);
  addLoop(loopLEDB);
  addLoop(loopLEDC);
}
// Loop program
void loop() {
  // Do nothing
  delay(1);
}