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
  Serial.println("Example: C 0");
  Serial.println("------------------");
}

void setup() {
  Serial.begin(115200);
  printHelp();
}

char inputBuffer[15];
int inputLen = 0;

void loop() {
  // Check if anything was sent
  if (!Serial.available()) return;
  // Read character
  char c = Serial.read();
  // Handle backspace
  if (c == '\b') {
    if (inputLen > 0) { inputLen--; Serial.print("\b \b"); }
    return;
  }
  // Capture character
  if (inputLen < sizeof(inputBuffer) && c != '\r' && c != '\n' && c != 0) {
    inputBuffer[inputLen++] = c;
    // Print character back to terminal
    Serial.print(c);
  }
  // Check if command was received
  if (!(c == '\r' || c == '\n' || c == 0)) return;
  Serial.println();
  Serial.flush(false);
  // Parse command
  inputBuffer[inputLen] = 0;
  char letter = inputBuffer[0];
  String pulseStr(inputBuffer+1, inputLen-1);
  pulseStr.trim();
  inputLen = 0;
  // Convert letter to index
  uint8_t portId = letter - ((letter > 'Z') ? 'a' : 'A');
  if (portId > 3 || pulseStr.isEmpty()) {
    printHelp();
    return;
  }
  // Check if port is available
  if (portId >= Servo.getPortsCount()) {
    Serial.printf("Port %c does not exist\n", 'A'+portId);
    return;
  }
  // Get motor control interface (dynamically)
  auto &servo = Servo[portId];
  // Move to position
  int pulse = pulseStr.toInt();
  servo.spinPulseRaw(pulse);
  Serial.printf("Servo %c pulse %dus, position: %d%%, angle: %ddeg", 'A'+portId, servo.getPulse(), servo.getPos(), servo.getAngle());
  Serial.println();
}
