#include <Arduino.h>
/*
  Module:  [14] Totem Line Follower
  RoboBoard example get value update inside event function.
*/
// Initialize Line Follower
TotemModule14 sensor;
// Define variables required for this example
int value[3];
uint8_t raw[8];
// Function to receive Line Follower module events
void sensorEvent(int evt) {
  // Check if received event is for "evtPos" parameter and update value
  if (evt == TotemModule14::evtPos) value[0] = sensor.getPos();
  // Check if receiver event is for "color"
  else if (evt == TotemModule14::evtColor) {
    value[1] = sensor.getColor();
    value[2] = sensor.isDetected();
  }
  else if (evt == TotemModule14::evtRaw) { sensor.getRaw(raw); }
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register event function for Distance module
  sensor.addEvent(sensorEvent);
  // Enable event broadcasting (required for events to works)
  sensor.getPos(); // Start receive TotemModule14::evtPos
  sensor.getColor(); // Start receive TotemModule14::evtColor
  sensor.getRaw(raw); // Start receive TotemModule14::evtRaw
}
// Loop program
void loop() {
  // Print module data
  Serial.printf("Position %3d Color: %c, Junction: %d, Raw: ", 
    value[0], value[1], value[2]
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