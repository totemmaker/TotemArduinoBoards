#include <Arduino.h>
/*
  Example to control DC motor ports trough Serial Monitor.
  Open Serial Monitor with 115200 baud rate and type in commands:
  "A invert" - flip motor A spin direction
  "B brake" - brake motor B
  "C -50" - spin motor C backwards at 50% power
  "D 60" - spin motor D forward at 50% power
  "F 50" - set motor (all) frequency to 50Hz
  "A slow" - set motor A to slow decay
  "B fast" - set motor A to fast decay
  
  Letters in range [A:D], power [-100:100]. 0 - stop.
*/
void printHelp() {
  Serial.println("Invalid command. Required format: (letter) (invert|brake|speed|slow|fast)");
  Serial.println("Example: A invert");
  Serial.println("Example: B brake");
  Serial.println("Example: C -50");
  Serial.println("Example: D 60");
  Serial.println("Change motor frequency:");
  Serial.println("Example: F 20000");
  Serial.println("Change decay mode:");
  Serial.println("Example: A slow");
  Serial.println("Example: B fast");
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
  // Convert letter to port index
  uint8_t portId = letter - ((letter > 'Z') ? 'a' : 'A');
  // Change frequency
  if (('A'+portId) == 'F' && !pulseStr.isEmpty()) {
    int freq = pulseStr.toInt();
    if (freq == 0) { Serial.println("Frequency can't be 0!"); return; }
    DC.setFrequency(pulseStr.toInt());
    Serial.printf("Changed motor frequency to %dHz\n", DC.getFrequency());
    return;
  }
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
  // Apply slow decay
  else if (pulseStr.equals("slow")) {
      motor.setSlowDecay(); // Set to slow
      Serial.printf("Motor %c decay - slow", 'A'+portId);
  }
  // Apply fast decay
  else if (pulseStr.equals("fast")) {
      motor.setFastDecay(); // Set to fast
      Serial.printf("Motor %c decay - fast", 'A'+portId);
  }
  // Apply spin power and direction
  else {
      int speed = pulseStr.toInt();
      motor.spin(speed);
      Serial.printf("Motor %c spin %s at %d%%", 'A'+portId, speed > 0 ? "forward" : "backward", abs(motor.getSpin()));
  }
  Serial.println();
}
