// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
}
// Loop program
void loop() {
  // Print ports info
  Serial.printf("Port: DC: %s, USB: %s\n",
    X4.isDC() ? "Plugged" : "Unplugged", 
    X4.isUSB()  ? "Plugged" : "Unplugger"
  );
  // Print battery info
  Serial.printf("Battery: voltage: %.2fV, low: %s, charging: %s (%ds)\n",
    X4.getBatteryVoltage(),
    X4.isBatteryLow()  ? "Yes" : "No",
    X4.isBatteryCharging()  ? "Yes" : "No",
    X4.getBatteryChargingTime()
  );
  // Print board info
  Serial.printf("Board: module: 04, serial: %d, revision: v%s, driver: v%s, software: v%s\n",
    X4.getSerial(),
    X4.getRevision(),
    X4.getDriverVersion(),
    X4.getSoftwareVersion()
  );
  // Delay 2 seconds
  delay(2000);
}