#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4 Revision v1.1
  Details: Example displaying I2C address of connected Qwiic modules

  WARNING: This example is for board revision v1.1.
           Revision number is printed on the top of RoboBoard.
*/
// Include I2C library
#include <Wire.h>
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Initialize I2C library
  Wire.begin();
}
// Loop program
void loop() {
  // Print header text
  Serial.println();
  Serial.println("Detected Qwiic modules:");
  // Variable to check if any module is detected
  bool isAnythingDetected = false;
  // Loop all available I2C addresses
  for (int address = 1; address < 127; address++) {
    // Start I2C transmission to selected address
    Wire.beginTransmission(address);
    // Get result of transmission
    int error = Wire.endTransmission();
    // Check if there was no error during transmission
    if (error == 0) {
      // Ignore on-board LSM6DS3 MEMS sensor at address 0x6A.
      // Connected to same I2C line as Qwiic
      if (address == 0x6A)
        continue; // Skip
      // Print detected address
      Serial.print("I2C address: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      // Mark that we found something
      isAnythingDetected = true;
    }
    // Check if there was other error during transmission
    else if (error != I2C_ERROR_ACK) {
      // Print detected error at selected address
      Serial.print("Error (");
      Serial.print(error);
      Serial.print(") at I2C address: 0x");
      Serial.println(address, HEX);
    }
  }
  // Print message if nothing was found
  if (!isAnythingDetected)
    Serial.println("None");
  // Loop every 3 seconds
  delay(3000);
}