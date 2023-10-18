#include <Arduino.h>
/*
  Example to display RoboBoard battery state.
  Open Serial Monitor to view output.
*/
// Initialize program
void setup() {
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Print battery info
  Serial.printf("-----Battery----\n");
  // Print State Of Charge (0-100%)
  Serial.printf("SOC: \t\t%d%%\n", Battery.getSOC());
  // Print voltage and other parameters
#if ROBOBOARD_X3 // getCurrent() and isCharging() only available in RoboBoard X3
    Serial.printf("Voltage:\t%.2fV %s\n", Battery.getVoltage(), Board.isUSB() ? "(USB)" : "");
    Serial.printf("Current:\t%.2fA\n", Battery.getCurrent());
    Serial.printf("Charging:\t%s\n", Battery.isCharging() ? "Yes" : "No");
#else // RoboBoard X4
    Serial.printf("Voltage:\t%.2fV\n", Battery.getVoltage());
#endif
  // Wait 1 second
  delay(1000);
}
