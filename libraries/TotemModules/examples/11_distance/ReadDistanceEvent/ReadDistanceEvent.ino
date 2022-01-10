#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to read distance without blocking code execution

  Note: Reading values directly (sensor.distance.getMM()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  This example shows how to use event functions to avoid blocking code.
*/
// Initialize Distance sensor
Module11 sensor;
// Define variables required for this example
float measurements[4]; // Storage for sensor data
bool updated;          // "true" when new sensor data received
int lastUpdate, lastEvent; // Hold last event time
// Function to receive Distance module events
void sensorEvent() {
  // Getting parameters inside event won't delay code execution.
  // Data is taken from current received event.
  // Check if received event is for "distance" parameter
  if (sensor.distance.isEvent()) {
    // Update measurement variable with latest data
    measurements[0] = sensor.distance.getMM();
    measurements[1] = sensor.distance.getCm();
    measurements[2] = sensor.distance.getFoot();
    measurements[3] = sensor.distance.getInch();
    updated = true; // Set that we have new data
    lastEvent = millis() - lastUpdate; // Get time between last event
    lastUpdate = millis(); // Update current event time
  }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function for Distance module
  sensor.addEvent(sensorEvent);
  // Enable events for distance parameter
  sensor.distance.event(); // When value is changed
  // sensor.distance.event(100); // Call event each 100ms
}
// Loop program
void loop() {
  // Check if event was received
  if (!updated)
    return;
  // Reset updated value
  updated = false;
  // Avoid overflowing Serial if events are too fast
  if (lastEvent < 70)
    delay(70);
  // Print distance units received from event
  Serial.printf("Distance: %4.0fmm, %3.0fcm, %4.2fft, %5.2fin, last update: %dms\n",
    measurements[0],
    measurements[1],
    measurements[2],
    measurements[3],
    lastEvent
  );
}