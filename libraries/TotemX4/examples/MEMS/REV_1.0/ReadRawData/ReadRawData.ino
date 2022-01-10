/*
  Board:  [X4] RoboBoard X4 revision 1.0
  Details: Example of Arduino LSM6DS3 library usage with RoboBoard X4
           to read Accelerometer and Gyroscope sensor data

  Install library: "Arduino LSM6DS3"
  GitHub: https://github.com/arduino-libraries/Arduino_LSM6DS3
*/
// Use Arduino LSM6DS3 library
#include <Arduino_LSM6DS3.h>
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Wait for Serial to initialize
  while (!Serial) {}
  // Check RoboBoard X4 revision
  if (strcmp(X4.getRevision(), "1.0") != 0)
    do { Serial.println("This tutorial is for RoboBoard X4 revision v1.0"); delay(1000); }
    while(1);
  // Initialize library and sensor
  if (!IMU.begin())
    do { Serial.println("Failed to communicate with LSM6DS3"); delay(1000); }
    while(1);
}
// Variables to store measurements data
float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
// Loop program
void loop() {
  // Read Acceleration measurements when available
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accX, accY, accZ);
  }
  // Read Gyroscope measurements when available
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
  }
  // Print measurements
  // Formatting: https://www.cplusplus.com/reference/cstdio/printf/
  Serial.printf("Acc: X:% 1.2f Y:% 1.2f Z:% 1.2f | Gyro: X:%4.f Y:%4.f Z:%4.f\n", 
      accX, accY, accZ, gyroX, gyroY, gyroZ);
}