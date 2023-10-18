#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  RoboBoard example to read line position.
*/
// Initialize Line Follower
TotemModule14 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Print module data
  Serial.printf("Position %3d Color: %c, Junction: %d, Accuracy: %2d%%, Raw: ", 
    sensor.getPos(),
    sensor.getColor(),
    sensor.isDetected(),
    sensor.getAccuracy()
  );
  // Read raw sensor values
  // Percentage in amount of light reflected
  // 100 - all light reflected (white surface)
  // 0 - none light reflected (black surface)
  uint8_t sensorRaw[8];
  sensor.getRaw(sensorRaw);
  for (int i=0; i<8; i++) {
    Serial.printf("%4d", sensorRaw[i]);
  }
  // Print new line
  Serial.println();
}