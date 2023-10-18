#include <Arduino.h>
/*
  RoboBoard X4 example to find connected TotemBUS modules
*/
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Start list of modules
  Serial.println("Connected module:");
  // Ping modules every 1s to receive their response
  // if (TotemModule::find(11)) { // Search for distance sensor module
  // if (TotemModule::find(11, 9724)) { // Search for distance sensor module with serial 9724
  if (TotemModule::find()) {
    // Print module information
    Serial.print("number: ");
    Serial.print(TotemModule::foundNumber);
    Serial.print(", serial: ");
    Serial.println(TotemModule::foundSerial);
  }
  else {
    Serial.println("No modules found");
  }
  // Wait 1s
  delay(1000);
}