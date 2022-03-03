#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to write analog values (PWM) to GPIO pins.
           Place a LED between GPIO pin and GND (with a resistor)
           to see output or use multimeter.
*/
// Initialize program
void setup() {
  // Use standard Arduino API to interact with GPIO pins
  pinMode(GPIOA, OUTPUT); // Set GPIOA to output mode
  pinMode(GPIOB, OUTPUT); // Set GPIOB to output mode
  pinMode(GPIOC, OUTPUT); // Set GPIOC to output mode
  pinMode(GPIOD, OUTPUT); // Set GPIOD to output mode
  // Set GPIOA pin to analog (PWM) output. Value can be between 0-255
  analogWrite(GPIOA, 50);
  // Set GPIOB pin to approximate 1.40 Volts. Value can be between 0-3300
  analogWriteMilliVolts(GPIOB, 1400);
  // Set GPIOC pin to analog (PWM) output. Value can be between 0-255
  analogWrite(GPIOC, 200);
}
// Loop program
void loop() {
  // Pulsate GPIO pin D between 0-255
  for (int i=0; i<255; i+=2) {
    analogWrite(GPIOD, i);
    delay(30);
  }
  for (int i=255; i>=0; i-=2) {
    analogWrite(GPIOD, i);
    delay(30);
  }
}