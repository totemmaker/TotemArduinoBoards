#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to read distance

  Note: Reading values directly (sensor.distance.getMM()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  If you want non-blocking code, check "Event" based example.
*/
// Initialize Distance sensor
Module11 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
}
// Loop program
void loop() {
  // Read distance with different measurement units
  Serial.printf("Distance: %4dmm, %4dcm, %4.2fft, %4.2fin\n",
    sensor.distance.getMM(),
    sensor.distance.getCm(),
    sensor.distance.getFoot(), // Returns float value (1.0)
    sensor.distance.getInch()  // Returns float value (1.0)
  );
  // Print every 100 milliseconds
  delay(100);
}