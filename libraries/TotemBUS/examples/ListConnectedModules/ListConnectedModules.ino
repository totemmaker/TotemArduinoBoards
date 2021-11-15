#include <Arduino.h>
/*
  Example: List connected TotemBUS modules
*/
// Prepare state variable
bool moduleFound = false;
// Function called on each module discovered
void moduleFoundEvent() {
  // Print module information
  Serial.print("number: ");
  Serial.print(X4.module.getLastNumber());
  Serial.print(", serial: ");
  Serial.println(X4.module.getLastSerial());
  // Mark at leas one module discovered
  moduleFound = true; 
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function to receive discovered modules
  X4.module.addEvent(moduleFoundEvent);
}
// Loop program
void loop() {
  // Start list of modules
  Serial.println("Connected modules:");
  // Ping modules every 1s to receive their response
  X4.module.ping(); // Ping all modules
  // X4.module.ping(11); // Ping dinstance sensor modules
  // X4.module.ping(11, 9724); // Ping specific dinstance sensor modules (with serial 9724)
  delay(1000); // Wait 1s for event to collect data
  // Print "none" message if nothing was found
  if (!moduleFound) {
    Serial.println("none");
  }
  moduleFound = false;
}