#include <Arduino.h>
/*
  WARNING: This example is for old revision (v1.0)
  of RoboBoard X4. Otherwise use standard Arduino
  pin functions "digitalWrite()"...

  Board:  [X4] RoboBoard X4 Revision v1.0
  RoboBoard example to interact with GPIO pins.
  GPIOA, GPIOB is set to output.
  GPIOC, GPIOD is set to input.
  Connect junper cable between GPIOA <-> GPIOC or
  GPIOB <-> GPIOD to light up LED.
*/
#if !ROBOBOARD_X4
#error "This example only works with RoboBoard X4"
#endif
// Initialize program
void setup() {
  // Use X4 functions GPIO pins
  X410_pinMode(GPIOA, OUTPUT); // Set GPIOA to OUTPUT
  X410_pinMode(GPIOB, OUTPUT); // Set GPIOB to OUTPUT
  X410_pinMode(GPIOC, INPUT_PULLDOWN);  // Set GPIOC to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
  X410_pinMode(GPIOD, INPUT_PULLDOWN);  // Set GPIOD to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
}
// Loop program
void loop() {
  // Variable to hold state rather LED should be turned on
  bool ledOn = false;
  X410_digitalWrite(GPIOA, HIGH); // Set GPIOA to HIGH (3.3 Volts -> VCC)
  // delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOC pin is pulled HIGH (jumper wire connected)
  if (X410_digitalRead(GPIOC) == HIGH) {
    ledOn = true;
  }
  X410_digitalWrite(GPIOA, LOW); // Set GPIOA to LOW (0 Volts -> GND)
  // Switch to other pin pair. The catch is if you connect GPIOA <-> GPIOD,
  // LED won't turn on, because it's incorrect pair
  X410_digitalWrite(GPIOB, HIGH);
  // delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOD pin is pulled HIGH (jumper wire connected)
  if (X410_digitalRead(GPIOD) == HIGH) {
    ledOn = true;
  }
  X410_digitalWrite(GPIOB, LOW);
  // Turn on LED
  LED.setState(ledOn);
  delay(100);
}