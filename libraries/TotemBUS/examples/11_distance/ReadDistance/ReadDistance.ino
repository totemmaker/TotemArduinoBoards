#include <Arduino.h>
#include <TotemModule11.h>
/*
  Module:  [11] Totem Distance sensor
  RoboBoard example to read distance
*/
// Initialize Line Follower
TotemModule11 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Read distance with different measurement units
  Serial.printf("Distance: %4dmm, %4dcm, %4.2fft, %4.2fin\n",
    sensor.getMM(),
    sensor.getCm(),
    sensor.getFoot(), // Returns float value (1.0)
    sensor.getInch()  // Returns float value (1.0)
  );
  // Print every 100 milliseconds
  delay(100);
}