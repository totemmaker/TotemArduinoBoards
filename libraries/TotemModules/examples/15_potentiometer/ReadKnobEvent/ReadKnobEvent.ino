#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  Details: Example showing how to read knob position and button state
           without blocking code execution.
           Also allows to change knob resolution by pressing A, C buttons
  
  Note: Reading values directly (sensor.knobA.get()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  This example shows how to use event functions to avoid blocking code.
*/
// Initialize Potentiometer module
Module15 pot;
// Current bits resolution
const int bits[] = {6, 8, 10, 12};
int currentBits = 1;
// Define variables required for this example
int knobValue[3];
int buttonValue[3];
// Function to receive Potentiometer module events
void potentiometerEvent() {
  // Getting parameters inside event won't delay code execution.
  // Data is taken from current received event.
  // If knob event, store position to variable
  if (pot.knob.isEvent(chA)) knobValue[0] = pot.knob.get(chA);
  if (pot.knob.isEvent(chB)) knobValue[1] = pot.knob.get(chB);
  if (pot.knob.isEvent(chC)) knobValue[2] = pot.knob.get(chC);
  // If button A pressed
  if (pot.button.isEvent(chA)) {
    // Store button state to variable
    buttonValue[0] = pot.button.isPressed(chA);
    // Check if button is pressed
    if (pot.button.isPressed(chA)) {
      // Decrement selected resolution
      if (currentBits > 0) currentBits--;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
  // If button B pressed, store state to variable
  if (pot.button.isEvent(chB)) buttonValue[1] = pot.button.isPressed(chB);
  // If button C pressed
  if (pot.button.isEvent(chC)) {
    // Store button state to variable
    buttonValue[2] = pot.button.isPressed(chC);
    // Check if button is pressed
    if (pot.button.isPressed(chC)) {
      // Increment selected resolution
      if (currentBits < 3) currentBits++;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function for Potentiometer module
  pot.addEvent(potentiometerEvent);
  // Enable events for knob & button parameters
  pot.knob.event(chA); // When value is changed
  pot.knob.event(chB); // When value is changed
  pot.knob.event(chC); // When value is changed
  pot.button.event(chA); // When value is changed
  pot.button.event(chB); // When value is changed
  pot.button.event(chC); // When value is changed
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