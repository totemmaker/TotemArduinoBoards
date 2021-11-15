/*
  Board:  [X4] RoboBoard X4
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
  // Initialize library
  IMU.begin();
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