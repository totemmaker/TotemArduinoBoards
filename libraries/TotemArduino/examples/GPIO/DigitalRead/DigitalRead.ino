#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to read digital values with GPIO pins.
           Run Serial Monitor at 9600 speed to view 
           Serial print output.
           Use jumper cable to connect pins to GND or VCC
           and see how it affects them.
*/
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Use standard Arduino API to interact with GPIO pins
  // Input pin can have 3 modes. They change pin behavior when
  // pin is not connected:
  // INPUT - floating, pin state is affected by noise (fluctuating)
  // INPUT_PULLUP - pin by default is drawn to HIGH state
  // INPUT_PULLDOWN - pin by default is drawn to LOW state
  pinMode(GPIOA, INPUT_PULLUP); // Set GPIOA to input with default LOW
  pinMode(GPIOB, INPUT_PULLDOWN); // Set GPIOB to input with default HIGH
  pinMode(GPIOC, INPUT_PULLDOWN); // Set GPIOC to input with default HIGH
  pinMode(GPIOD, INPUT); // Set GPIOD to input with floating mode
}
// Loop program
void loop() {
  // Read digital value of GPIO pins
  // Will return value LOG or HIGH (0 Volt (GND) or 3.3 Volt (VCC))
  int gpioA = digitalRead(GPIOA);
  int gpioB = digitalRead(GPIOB);
  int gpioC = digitalRead(GPIOC);
  int gpioD = digitalRead(GPIOD);
  // Print GPIO pin values
  Serial.printf("GPIO A: %4s, B: %4s, C: %4s, D: %4s\n",
    gpioA == LOW ? "LOW" : "HIGH",
    gpioB == LOW ? "LOW" : "HIGH",
    gpioC == LOW ? "LOW" : "HIGH",
    gpioD == LOW ? "LOW" : "HIGH"
    );
  // Wait for 100 milliseconds
  delay(100);
}