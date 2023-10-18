#include <Arduino.h>
/*
  Module:  [11] Distance sensor module
  RoboBoard example to control two identical modules at the same time.
  Module 1 is set to GREEN color.
  Module 2 is set to RED color.
  Module 1 color will react to Module 2 distance.
  Module 2 color will react to Module 1 distance.
*/
// Initialize Distance sensor
// These objects will only control specific
// connected modules, identified by serial number
// Initialize Line Follower
TotemModule11 sensor1(9724); // Init module 11 with serial 9724
TotemModule11 sensor2(9740); // Init module 11 with serial 9740
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Update Module 1 color (GREEN) with distance data received from Module 2
  // Module 2 distance is constrained to [0:255] and inverted to color GREEN
  sensor1.rgb.color(
    0, 255-constrain(sensor2.getMM(), 0, 255), 0 // red, green, blue
  );
  // Update Module 2 color (RED) with distance data received from Module 1
  // Module 1 distance is constrained to [0:255] and inverted to color RED
  sensor2.rgb.color(
    255-constrain(sensor1.getMM(), 0, 255), 0, 0 // red, green, blue
  );
  // Delay 30ms between updates
  delay(30);
}