#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  Details: Example showing how to read module data without blocking code execution
  
  Note: Reading values directly (sensor.linePos.get()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  This example shows how to use event functions to avoid blocking code.
*/
// Initialize Line Follower
Module14 sensor;
// Define variables required for this example
int value[4];
uint8_t raw[8];
// Function to receive Line Follower module events
void sensorEvent() {
  // Getting parameters inside event won't delay code execution.
  // Data is taken from current received event.
  // Check if received event is for "pos" parameter and update value
  if (sensor.linePos.isEvent()) value[0] = sensor.linePos.get();
  // Check if receiver event is for "color"
  else if (sensor.lineColor.isEvent()) value[1] = sensor.lineColor.get();
  else if (sensor.lineCross.isEvent()) value[2] = sensor.lineCross.isDetected();
  else if (sensor.lineRange.isEvent()) value[3] = sensor.lineRange.get();
  else if (sensor.lineRaw.isEvent()) { sensor.lineRaw.get(raw); }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function for Distance module
  sensor.addEvent(sensorEvent);
  // Enable events for distance parameter
  sensor.linePos.event(); // When value is changed
  sensor.lineColor.event(100); // Call event each 100ms
  sensor.lineCross.event(100); // Call event each 100ms
  sensor.lineRange.event(100); // Call event each 100ms
  sensor.lineRaw.event(200); // Call event each 200ms
}
// Loop program
void loop() {
  // Print module data
  Serial.printf("Position %3d Color: %c, Junction: %d, Accuracy: %2d%%, Raw: ", 
    value[0], value[1], value[2], value[3]
  );
  // Read raw sensor values
  // Percentage in amount of light reflected
  // 100 - all light reflected (white surface)
  // 0 - none light reflected (black surface)
  for (int i=0; i<8; i++) {
    Serial.printf("%4d", raw[i]);
  }
  // Print new line
  Serial.println();
  // Delay printing
  delay(50);
}