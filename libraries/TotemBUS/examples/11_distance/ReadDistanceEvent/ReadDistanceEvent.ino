#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  RoboBoard example get distance value update inside event function.
*/
// Initialize Line Follower
TotemModule11 sensor;
// Define variables required for this example
float measurements[4]; // Storage for sensor data
bool updated;          // "true" when new sensor data received
int lastUpdate, lastEvent; // Hold last event time
// Function to receive Distance module events
void sensorEvent(int evt) {
  // Check if received event is for "distance" parameter
  if (evt == TotemModule11::evtDistance) {
    // Update measurement variable with latest data
    measurements[0] = sensor.getMM();
    measurements[1] = sensor.getCm();
    measurements[2] = sensor.getFoot();
    measurements[3] = sensor.getInch();
    updated = true; // Set that we have new data
    lastEvent = millis() - lastUpdate; // Get time between last event
    lastUpdate = millis(); // Update current event time
  }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register event function for Distance module
  sensor.addEvent(sensorEvent);
  // Request data from module (required for events to works)
  sensor.getMM();
  sensor.getMM(); // Will start distance value broadcasting
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