#include <Arduino.h>
/*
  RoboBoard example to override button click of Totem mobile App.
  Usually button (widget) press will directly apply motor power.
  This example allows to intercept these motor commands or
  block them from further execution. Received "value" can be used
  for custom implementation.
*/
// Event function called when app button is clicked
bool appOverride(int cmd, int value) {
  if (cmd == TotemApp.cmdPosA) {
    Serial.print("/0/serv/posA -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPosB) {
    Serial.print("/0/serv/posB -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPosC) {
    Serial.print("/0/serv/posC -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPowerA) {
    Serial.print("/0/dc/powerA -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPowerB) {
    Serial.print("/0/dc/powerB -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPowerC) {
    Serial.print("/0/dc/powerC -> "); Serial.println(value);
  }
  if (cmd == TotemApp.cmdPowerD) {
    Serial.print("/0/dc/powerD -> "); Serial.println(value);
  }
  // This function requires return!
  // `true` - pass received command back to RoboBoard
  // `false` - RoboBoard won't get this command (override)
  return false;
}
// Initialize program
void setup() {
  // Register Totem App event function
  TotemApp.addOverride(appOverride);
  // TotemApp.begin() is called internally by "TotemApp.addOverride()"
}
// Loop program
void loop() {
  // Empty
}
