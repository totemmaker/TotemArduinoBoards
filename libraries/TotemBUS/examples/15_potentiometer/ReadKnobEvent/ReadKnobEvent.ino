#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  RoboBoard example to read knob position and button state inside event function.
  Also allows to change knob resolution by pressing A, C buttons.
*/
// Initialize Potentiometer module
TotemModule15 pot;
// Current bits resolution
const int bits[] = {6, 8, 10, 12};
int currentBits = 1;
// Define variables required for this example
int knobValue[3];
int buttonValue[3];
// Function to receive Potentiometer module events
void potentiometerEvent(int evt) {
  // If knob event, store position to variable
  if (evt == TotemModule15::evtKnobA) knobValue[0] = pot.getKnobA();
  if (evt == TotemModule15::evtKnobB) knobValue[1] = pot.getKnobB();
  if (evt == TotemModule15::evtKnobC) knobValue[2] = pot.getKnobC();
  // If button A pressed
  if (evt == TotemModule15::evtButtonA) {
    // Store button state to variable
    buttonValue[0] = pot.getButtonA();
    // Check if button is pressed
    if (pot.getButtonA()) {
      // Decrement selected resolution
      if (currentBits > 0) currentBits--;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
  // If button B pressed, store state to variable
  if (evt == TotemModule15::evtButtonB) buttonValue[1] = pot.getButtonB();
  // If button C pressed
  if (evt == TotemModule15::evtButtonC) {
    // Store button state to variable
    buttonValue[2] = pot.getButtonC();
    // Check if button is pressed
    if (pot.getButtonC()) {
      // Increment selected resolution
      if (currentBits < 3) currentBits++;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register event function for Potentiometer module
  pot.addEvent(potentiometerEvent);
  // Enable events for knob & button parameters (required for events to works)
  pot.getKnobA(); // Start events of KnobA
  pot.getKnobB(); // Start events of KnobB
  pot.getKnobC(); // Start events of KnobC
  pot.getButtonA(); // Start events of ButtonA
  pot.getButtonB(); // Start events of ButtonB
  pot.getButtonC(); // Start events of ButtonC
}

// Loop program
void loop() {
  // Print stored values
  Serial.printf("Knob A: %4d B: %4d C: %4d, Button A: %d B: %d C: %d, Bits: %d\n", 
    knobValue[0], knobValue[1], knobValue[2],
    buttonValue[0], buttonValue[1], buttonValue[2],
    bits[currentBits]
  );
  // Delay printing
  delay(50);
}