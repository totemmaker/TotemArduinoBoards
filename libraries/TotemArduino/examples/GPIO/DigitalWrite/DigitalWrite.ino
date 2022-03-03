#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to read digital values with GPIO pins.
           Change state of GPIO pins. You can use multimeter
           to read state changes.
*/
// Initialize program
void setup() {
  // Use standard Arduino API to interact with GPIO pins
  pinMode(GPIOA, OUTPUT); // Set GPIOA to output mode
  pinMode(GPIOB, OUTPUT); // Set GPIOB to output mode
  pinMode(GPIOC, OUTPUT); // Set GPIOC to output mode
  pinMode(GPIOD, OUTPUT); // Set GPIOD to output mode
  // Set GPIO A pin to HIGH (3.3V (VCC))
  digitalWrite(GPIOA, HIGH);
  // Set GPIO B pin to LOW (0V (GND))
  digitalWrite(GPIOB, LOW);
}
// Loop program
void loop() {
  // Toggle GPIO C & D pins
  digitalWrite(GPIOC, HIGH);
  digitalWrite(GPIOD, LOW);
  digitalWrite(LED_BUILTIN, HIGH); // Demonstrate this function on LED
  delay(1000); // Wait for 1 second
  digitalWrite(GPIOC, LOW);
  digitalWrite(GPIOD, HIGH);
  digitalWrite(LED_BUILTIN, LOW); // Demonstrate this function on LED
  delay(1000); // Wait for 1 second
}