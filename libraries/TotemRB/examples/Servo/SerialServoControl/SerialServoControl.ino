#include <Arduino.h>
/*
  Example to control Servo motor ports trough Serial Monitor.
  Open Serial Monitor with 115200 baud rate and type in commands:
  "A 500" - set motor A position to 500us
  "B 2500" - set motor B position to 2500us
  "C 0" - set motor C to coast (free spin)
  Letters in range [A:C]
*/
void printHelp() {
  Serial.println("Invalid command. Required format: (letter) (pulse us)");
  Serial.println("Example: A 500");
  Serial.println("Example: B 2500");
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
  if (Board.getNumber() == 3 && portId == 2) {
    Serial.println("Port C does not exist");
    return;
  }
  if (portId > 2 || pulseStr.isEmpty()) {
    printHelp();
    return;
  }
  // Get motor control interface (dynamically)
  auto &servo = Servo[portId];
  // Move to position
  int pulse = pulseStr.toInt();
  servo.spinPulseRaw(pulse);
  Serial.printf("Servo %c pulse %dus, position: %d, angle: %ddeg", 'A'+portId, servo.getPulse(), servo.getPos(), servo.getAngle());
  Serial.println();
}
