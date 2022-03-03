#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  Details: Example showing how to read knob position and button state
           without blocking code execution.
           Also allows to change knob resolution by pressing A, C buttons

  Note: Reading values without event (pot.knob.getPosition()) delays code for
  ~1ms. Function will send request to module and awaits for response.
  Same as I2C based communication.
  This example toggles events on / off and measures time required to call function.
  When events are enabled - module starts to broadcast value changes, which are stored in
  internal buffer. Latest stored value is returned on function call.
*/
// Initialize Potentiometer module
Module15 pot;
// Current bits resolution
const int bits[] = {6, 8, 10, 12};
int currentBits = 1;
// Define variables required for this example
bool eventsStarted; // State if events are enabled
int eventsCount; // Amount of times event was called
// Function to receive Potentiometer module events
void potentiometerEvent() {
  // If button A pressed
  if (pot.button.isEvent(chA)) {
    // Check if button is pressed
    if (pot.button.isPressed(chA)) {
      // Decrement selected resolution
      if (currentBits > 0) currentBits--;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
  // If button C pressed
  if (pot.button.isEvent(chC)) {
    // Check if button is pressed
    if (pot.button.isPressed(chC)) {
      // Increment selected resolution
      if (currentBits < 3) currentBits++;
      // Set new selected resolution
      pot.setKnobBits(bits[currentBits]);
    }
  }
  // Increment events counter
  eventsCount++;
}
// Parallel loop to toggle events
void loopToggleEvents() {
  // Start sending events from module
  pot.knob.eventStart(chAll);
  pot.button.eventStart(chAll);
  eventsStarted = true;
  delay(3000); // Wait 3 seconds
  // Stop sending events from module
  pot.knob.eventStop(chAll);
  pot.button.eventStop(chAll);
  eventsStarted = false;
  eventsCount = 0; // Reset counter
  delay(3000); // Wait 3 seconds
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function to detect button press
  // Optional. In case required to know when value is updated
  pot.addEvent(potentiometerEvent);
  // Create parallel loop to toggle events
  addLoop(loopToggleEvents);
}
// Loop program
void loop() {
  // Measure time (microseconds) it takes to receive value from module
  int start, end, total;
  start = micros(); // Save time before call
  int knobA = pot.knob.getPosition(chA);
  int knobB = pot.knob.getPosition(chB);
  int knobC = pot.knob.getPosition(chC);
  int buttonA = pot.button.isPressed(chA);
  int buttonB = pot.button.isPressed(chB);
  int buttonC = pot.button.isPressed(chC);
  end = micros(); // Save time after call
  // Total time taken to read value from module
  total = end-start;
  // Print information
  Serial.printf("Knob A: %4d B: %4d C: %4d, Button A: %d B: %d C: %d, Bits: %d. Events: %s %d. Time: %dus.\n",
    knobA, knobB, knobC, buttonA, buttonB, buttonC, bits[currentBits],
    eventsStarted ? "on" : "off", eventsCount, total
  );
  // Delay printing
  delay(70);
}