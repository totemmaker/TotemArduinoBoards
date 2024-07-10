#include <Arduino.h>
/*
  Communication with external ESP32 board using Totem Arduino library.
  https://github.com/totemmaker/TotemArduino
  RoboBoard works as remotely controlled (Bluetooth) module and is able to intercept
  Totem Library functions: "sendValue", "sendString", "readValue", "readString".

  RoboBoard can also stream some values back to Totem Library (intercepted by onValue and onString)
  
  Use with example code:
  https://github.com/totemmaker/TotemArduino/blob/master/examples/BLE/RoboBoardSendRead/RoboBoardSendRead.ino

  This functionality can be used to implement custom RoboBoard control interface
  to perform any actions (like spin a motor) or read some values (like sensors).
  https://docs.totemmaker.net/roboboard/api/totemapp/
*/
// Detect connection event
void appEvent(int evt, int value) {
  if (evt == TotemApp.evtConnect) Serial.printf("Totem Library connected\n");
  if (evt == TotemApp.evtDisconnect) Serial.printf("Totem Library disconnected\n");
}
// Intercept value sent by sendValue() (from Totem Library)
void onSendValue(int id, int value) {
  switch (id) {
  // Control motor with matching ID
  case 0: DC.A.spin(value); break;
  case 1: DC.B.spin(value); break;
  // Spin servo to position or change speed
  case 10: Servo.A.spinPos(value); break;
  case 20: Servo.A.setSpeedRPM(value); break;
  // Print if other ID is received
  default: Serial.printf("Got ID: %d, value: %d\n", id, value);
  }
}
// Intercept string sent by sendString() (from Totem Library)
void onSendString(int id, String string) {
  switch (id) {
  // Change board name
  case 0: Board.setName(string.c_str()); break;
  // Print if other ID is received
  default: Serial.printf("Got ID: %d, string: %s\n", id, string.c_str());
  }
}
// Return value requested by readValue() (from Totem Library)
int onReadValue(int id) {
  switch (id) {
  // Return motors spin values
  case 0: return DC.A.getSpin();
  case 1: return DC.B.getSpin();
  // Return servo position
  case 10: return Servo.A.getPos();
  case 11: return Servo.A.getAngle();
  case 12: return Servo.A.getPulse();
  // Print if other ID is received
  default: Serial.printf("Read value ID: %d\n", id);
  }
  return 0;
}
// Return string requested by readString() (from Totem Library)
String onReadString(int id) {
  switch (id) {
  // Return configured name
  case 0: return Board.getName();
  default: Serial.printf("Read string ID: %d\n", id);
  }
  return "";
}

// Initialize program
void setup() {
  Serial.begin(115200);
  // Start Totem App service
  TotemApp.begin();
  // Register connection events
  TotemApp.addEvent(appEvent);
  // Register value handlers
  TotemApp.addOnSend(onSendValue);
  TotemApp.addOnSend(onSendString);
  TotemApp.addOnRead(onReadValue);
  TotemApp.addOnRead(onReadString);
}
// Loop program
uint32_t nextMillis = 0;
void loop() {
  // Stream servo A position Totem Library (when moving)
  if (Servo.A.isMoving()) {
    TotemApp.sendValue(0, Servo.A.getPos());
    delay(100);
  }
  else if (millis() > nextMillis) {
    // Send string of millis() on ID 1 to Totem Library
    TotemApp.sendString(1, String(millis()));
    // Repeats every 1s
    nextMillis = millis() + 1000;
  }
}
