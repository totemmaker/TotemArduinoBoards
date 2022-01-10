/*
  Board:  [X4] RoboBoard X4 rev 1.1
  Details: Example of ICM20689 library usage with RoboBoard X4
           to read Accelerometer and Gyroscope sensor data

  Install library: "ICM20689"
  GitHub: https://github.com/finani/ICM20689
*/
// Use ICM20689 library
#include <ICM20689.h>
// Declare IMU object
ICM20689 IMU(Wire, 0x68);
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Wait for Serial to initialize
  while (!Serial) {}
  // Check RoboBoard X4 revision
  if (strcmp(X4.getRevision(), "1.0") == 0)
    do { Serial.println("This tutorial is for RoboBoard X4 revision v1.1"); delay(1000); }
    while(1);
  // Initialize library and sensor
  if (IMU.begin() < 0)
    do { Serial.println("Failed to communicate with ICM20689"); delay(1000); }
    while(1);
}
// Loop program
void loop() {
  // Read Acceleration and Gyroscope measurements
  IMU.readSensor();
  // Print measurements
  // Formatting: https://www.cplusplus.com/reference/cstdio/printf/
  Serial.printf("Acc: X:% 1.2f Y:% 1.2f Z:% 1.2f | Gyro: X:% 1.4f Y:% 1.4f Z:% 1.4f\n", 
      IMU.getAccelX_mss(), IMU.getAccelY_mss(), IMU.getAccelZ_mss(),
      IMU.getGyroX_rads(), IMU.getGyroY_rads(), IMU.getGyroZ_rads());
}