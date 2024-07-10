#include <Arduino.h>
/*
  RoboBoard example to scan for I2C modules connected to Qwiic port
*/
// Include I2C library
#include <Wire.h>
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Initialize I2C library (100kHz speed)
  Wire.begin();
  // Change I2C frequency if required. By default: 400kHz
  // Wire.begin(SDA, SCL, 100000); // set to 100kHz
  // SDA, SCL are definitons of pins, connected to Qwiic port
  // Recommendation:
  // For Qwiic port use "Wire"
  // For GPIO pins use "Wire1"
}
// Loop program
void loop() {
  // Print header text
  Serial.println();
  Serial.println("Detected Qwiic modules:");
  // Variable to check if any module is detected
  bool isAnythingDetected = false;
  // Loop all available I2C addresses
  int address = 0x01;
  int endAddress = 0x7D;
  // Loop all I2C devices
  for (; address <= endAddress; address++) {
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