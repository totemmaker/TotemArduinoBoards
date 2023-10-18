#include <Arduino.h>
/*
  Example to control DC motor ports trough Serial Monitor.
  Open Serial Monitor with 115200 baud rate and type in commands:
  "A invert" - flip motor A spin direction
  "B brake" - brake motor B
  "C -50" - spin motor C backwards at 50% power
  "D 60" - spin motor D forward at 50% power
  Letters in range [A:D], power [-100:100]. 0 - stop.
*/
void printHelp() {
  Serial.println("Invalid command. Required format: (letter) (invert|brake|speed)");
  Serial.println("Example: A invert");
  Serial.println("Example: B brake");
  Serial.println("Example: C -50");
  Serial.println("Example: D 60");
  Serial.println("------------------");
}

void setup() {
  Serial.begin(115200);
  printHelp();
}

void loop() {
  // Check if anything was sent
  if (!Serial.available()) return;
  // Parse serial command
  char letter = Serial.read(); // Read letter
  String pulseStr = Serial.readString();
  pulseStr.trim();
  // Convert letter to index
  uint8_t portId = letter - ((letter > 'Z') ? 'a' : 'A');
  if (portId > 3 || pulseStr.isEmpty()) {
    printHelp();
    return;
  }
  // Get motor control interface (dynamically)
  auto &motor = DC[portId];
  // Invert spin direction
  if (pulseStr.equals("invert")) {
      motor.setInvert(!motor.getInvert());
      Serial.printf("Motor %c spin direction inverted - %s", 'A'+portId, motor.getInvert() ? "true" : "false");
  }
  // Apply brake
  else if (pulseStr.equals("brake")) {
      motor.brake();
      Serial.printf("Motor %c brake", 'A'+portId);
  }
  // Apply spin power and direction
  else {
      int speed = pulseStr.toInt();
      motor.spin(speed);
      Serial.printf("Motor %c spin %s at %d%%", 'A'+portId, speed > 0 ? "forward" : "backward", abs(motor.getSpin()));
  }
  Serial.println();
}
