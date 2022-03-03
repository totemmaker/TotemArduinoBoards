#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to read distance without blocking code execution

  Note: Reading values without event (sensor.distance.getMM()) delays code for
  ~1ms. Function will send request to module and awaits for response.
  Same as I2C based communication.
  This example toggles events on / off and measures time required to call function.
  When events are enabled - module starts to broadcast value changes, which are stored in
  internal buffer. Latest stored value is returned on function call.
*/
// Initialize Distance sensor
Module11 sensor;
// Define variables required for this example
bool eventsStarted; // State if events are enabled
int eventsCount; // Amount of times event was called
// Function to receive Distance module events
void sensorEvent() {
  // Check if received "distance" event
  if (sensor.distance.isEvent()) {
    // Display red color if distance closer than 10cm
    if (sensor.distance.getCm() < 10 && sensor.distance.isDetected())
      sensor.rgb.colorHEX(chAll, Color::Red);
    else
      sensor.rgb.colorHEX(chAll, Color::Green);
  }
  // Increment events counter
  eventsCount++;
}
// Parallel loop to toggle events
void loopToggleEvents() {
  // Start sending events from module
  sensor.distance.eventStart();
  eventsStarted = true;
  delay(3000); // Wait 3 seconds
  // Stop sending events from module
  sensor.distance.eventStop();
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
  int distMM = sensor.distance.getMM();
  end = micros(); // Save time after call
  // Total time taken to read value from module
  total = end-start;
  // Print information
  Serial.printf("Distance: %4dmm. Events: %s %d. Time: %dus.\n",
    distMM, eventsStarted ? "on" : "off", eventsCount, total
  );
  // Delay printing
  delay(70);
}
