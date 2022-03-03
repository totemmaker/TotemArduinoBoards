#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  Details: Example showing how to read module data
  
  Note: Reading values directly (sensor.pos.get()) delays code for
  ~1ms. Function will send request to module and and awaits for response.
  Same as I2C based communication.
  If you want non-blocking code, check "Event" based example.
*/
// Initialize Line Follower
Module14 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
}
// Loop program
void loop() {
  // Print module data
  Serial.printf("Position %3d Color: %c, Detected: %3s, Accuracy: %2d%%, Raw: ", 
    sensor.line.getPosition(),
    sensor.line.getColor(),
    sensor.line.isDetected() ? "yes" : "no",
    sensor.sensor.getAccuracy()
  );
  // Read raw sensor values
  // Percentage in amount of light reflected
  // 100 - all light reflected (white surface)
  // 0 - none light reflected (black surface)
  uint8_t sensorRaw[8];
  sensor.sensor.getRaw(sensorRaw);
  for (int i=0; i<8; i++) {
    Serial.printf("%4d", sensorRaw[i]);
  }
  // Print new line
  Serial.println();
}