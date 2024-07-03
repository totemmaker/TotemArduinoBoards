#include <Arduino.h>
#include <TotemModule15.h>
/*
  Module:  [15] Totem Potentiometer module
  RoboBoard example to read knob position and button state.
*/
// Initialize Potentiometer module
TotemModule15 pot;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Print knob & button values
  Serial.printf("Knob A: %4d B: %4d C: %4d, Button A: %d B: %d C: %d\n", 
    pot.getKnobA(), pot.getKnobB(), pot.getKnobC(),
    pot.getButtonA(), pot.getButtonB(), pot.getButtonC()
  );
  // Delay printing
  delay(50);
}