#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4 Revision v1.1
  RoboBoard example to interact with GPIO pins.
  GPIOA, GPIOB is set to output.
  GPIOC, GPIOD is set to input.
  Connect junper cable between GPIOA <-> GPIOC or
  GPIOB <-> GPIOD to light up LED.
*/
// Initialize program
void setup() {
  // Use standard Arduino API to interact with GPIO pins
  pinMode(GPIOA, OUTPUT); // Set GPIOA to OUTPUT
  pinMode(GPIOB, OUTPUT); // Set GPIOB to OUTPUT
  pinMode(GPIOC, INPUT_PULLDOWN);  // Set GPIOC to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
  pinMode(GPIOD, INPUT_PULLDOWN);  // Set GPIOD to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
}
// Loop program
void loop() {
  // Variable to hold state rather LED should be turned on
  bool ledOn = false;
  digitalWrite(GPIOA, HIGH); // Set GPIOA to HIGH (3.3 Volts -> VCC)
  delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOC pin is pulled HIGH (jumper wire connected)
  if (digitalRead(GPIOC) == HIGH) {
    ledOn = true;
  }
  digitalWrite(GPIOA, LOW); // Set GPIOA to LOW (0 Volts -> GND)
  // Switch to other pin pair. The catch is if you connect GPIOA <-> GPIOD,
  // LED won't turn on, because it's incorrect pair
  digitalWrite(GPIOB, HIGH);
  delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOD pin is pulled HIGH (jumper wire connected)
  if (digitalRead(GPIOD) == HIGH) {
    ledOn = true;
  }
  digitalWrite(GPIOB, LOW);
  // Turn on LED
  LED.setState(ledOn);
  delay(100);
}