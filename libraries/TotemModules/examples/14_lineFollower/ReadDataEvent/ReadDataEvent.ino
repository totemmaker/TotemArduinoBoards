#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  Details: Example showing how to read module data without blocking code execution
  
  Note: Reading values without event (sensor.line.getPosition()) delays code for
  ~1ms. Function will send request to module and awaits for response.
  Same as I2C based communication.
  This example toggles events on / off and measures time required to call function.
  When events are enabled - module starts to broadcast value changes, which are stored in
  internal buffer. Latest stored value is returned on function call.
*/
// Initialize Line Follower
Module14 sensor;
// Define variables required for this example
bool eventsStarted; // State if events are enabled
int eventsCount; // Amount of times event was called
// Function to receive Line Follower module events
void sensorEvent() {
  // Check if received event is for "line" feature
  if (sensor.line.isEvent()) {
    // Set Green color if sensor is detecting a line
    if (sensor.line.isDetected())
      X4.rgb.colorHEX(chAll, Color::Green);
    else
      X4.rgb.colorHEX(chAll, Color::Red);
  }
  // Increment events counter
  eventsCount++;
}
// Parallel loop to toggle events
void loopToggleEvents() {
  // Start sending events from module
  sensor.line.eventStart();
  eventsStarted = true;
  delay(3000); // Wait 3 seconds
  // Stop sending events from module
  sensor.line.eventStop();
  eventsStarted = false;
  eventsCount = 0; // Reset counter
  delay(3000); // Wait 3 seconds
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function to change colors
  // Optional. In case required to know when value is updated
  sensor.addEvent(sensorEvent);
  // Create parallel loop to toggle events
  addLoop(loopToggleEvents);
}
// Loop program
void loop() {
  // Measure time (microseconds) it takes to receive value from module
  int start, end, total;
  start = micros(); // Save time before call
  int pos = sensor.line.getPosition();
  char color = sensor.line.getColor();
  end = micros(); // Save time after call
  // Total time taken to read value from module
  total = end-start;
  // Print information
  Serial.printf("Position %3d Color: %c. Events: %s %d. Time: %dus.\n",
    pos, color, eventsStarted ? "on" : "off", eventsCount, total
  );
  // Delay printing
  delay(70);
}
