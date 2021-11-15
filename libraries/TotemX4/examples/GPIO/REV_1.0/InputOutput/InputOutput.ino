#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4 Revision v1.0
  Details: Example how to interact with GPIO pins.
           GPIOA, GPIOB is set to output.
           GPIOC, GPIOD is set to input.
           Connect junper cable between GPIOA <-> GPIOC or
           GPIOB <-> GPIOD to light up LED.

  WARNING: This example is for board revision v1.0.
           For v1.1 examples check GPIO_REV1.1.
           Revision number is printed on the top of RoboBoard.
*/
// Initialize program
void setup() {
  // Use X4 functions GPIO pins
  X4.gpioC.pullMode(LOW);  // Set GPIOC to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
  X4.gpioD.pullMode(LOW);  // Set GPIOD to INPUT with pulling to LOW (when noting is connected. Prevent from floating)
}
// Loop program
void loop() {
  // Variable to hold state rather LED should be turned on
  bool ledOn = false;
  X4.gpioA.digitalWrite(HIGH); // Set GPIOA to HIGH (3.3 Volts -> VCC)
  // delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOC pin is pulled HIGH (jumper wire connected)
  if (X4.gpioC.digitalRead() == HIGH) {
    ledOn = true;
  }
  X4.gpioA.digitalWrite(LOW); // Set GPIOA to LOW (0 Volts -> GND)
  // Switch to other pin pair. The catch is if you connect GPIOA <-> GPIOD,
  // LED won't turn on, because it's incorrect pair
  X4.gpioB.digitalWrite(HIGH);
  // delayMicroseconds(1); // ESP32 is fast. Wait for pin to charge
  // Read if GPIOD pin is pulled HIGH (jumper wire connected)
  if (X4.gpioD.digitalRead() == HIGH) {
    ledOn = true;
  }
  X4.gpioB.digitalWrite(LOW);
  // Turn on LED
  X4.led.set(ledOn);
  delay(100);
}