#include <Arduino.h>
/*
  RoboBoard example to scan (selected) GPIO pins for connected I2C devices
  On RoboBoard X3 connect SDA : IO32, SCL : IO33
  On RoboBoard X4 connect SDA : GPIOA, SCL : GPIOB
*/
// Include I2C library
#include <Wire.h>
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Initialize I2C library (100kHz speed)
#if ROBOBOARD_X3
  Wire.begin(IO32, IO33); // Select IO32 as SDA, IO33 as SCL
#endif
#if ROBOBOARD_X4
  Wire.begin(GPIOA, GPIOB); // Select GPIOA as SDA, GPIOB as SCL
#endif
  // Change I2C frequency (speed) if required
  // Wire.begin(SDA, SCL, 400000); // set to 400kHz
  // SDA, SCL are definitons of pins, connected to Qwiic port
  // Recommendation:
  // For Qwiic port use "Wire"
  // For GPIO pins use "Wire1"
}
// Loop program
void loop() {
  // Print header text
  Serial.println();
  Serial.println("Detected I2C modules:");
  // Variable to check if any module is detected
  bool isAnythingDetected = false;
  // Loop all available I2C addresses
  int address = 0x01;
  int endAddress = 0x7F;
  // Loop all I2C devices
  for (; address < endAddress; address++) {
    // Start I2C transmission to selected address
    Wire.beginTransmission(address);
    // Get result of transmission
    int error = Wire.endTransmission();
    // Check if there was no error during transmission
    if (error == 0) {
      // Print detected address
      Serial.print("I2C address: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      // IMU sensor is connected to Qwiic
      // I2C line. Print sensor name
      if (IMU.isI2CAddr(address)) {
        Serial.print(" (");
        Serial.print(IMU.getName());
        Serial.print(")");
      }
      Serial.println();
      // Mark that we found something
      isAnythingDetected = true;
    }
  }
  // Print message if nothing was found
  if (!isAnythingDetected)
    Serial.println("None");
  // Loop every 3 seconds
  delay(3000);
}