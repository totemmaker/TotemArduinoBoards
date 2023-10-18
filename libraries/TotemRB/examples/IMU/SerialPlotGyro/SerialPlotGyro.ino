#include <Arduino.h>
#include <Wire.h>
/*
  RoboBoard example to view gyroscope measurements on
  Arduino IDE Serial Plotter.
  1. Upload this example
  2. Open Tools -> Serial Plotter
  3. Select 115200 baud rate
*/
// Initialize program
void setup() {
  // Start Serial communication at 115200 speed
  Serial.begin(115200);
  // Start I2C at 400kHz speed
  // SDA, SCL pins shares IMU sensor and Qwiic port
  Wire.begin(SDA, SCL, 400000);
  // SDA, SCL are definitons of pins, connected to Qwiic port
}
// Loop program
void loop() {
  // Read measurements from the sensor and store to "result" variable
  auto result = IMU.read();
  // Print measurements
  Serial.printf("GyroX:%.f,", result.getX_dps());
  Serial.printf("GyroY:%.f,", result.getY_dps());
  Serial.printf("GyroZ:%.f\n", result.getZ_dps());
  delay(25); // Wait 25 milliseconds
}
