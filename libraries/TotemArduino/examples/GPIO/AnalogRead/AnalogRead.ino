#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to read analog values with GPIO pins.
           Run Serial Monitor at 9600 speed to view 
           Serial print output.
*/
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Use standard Arduino API to interact with GPIO pins
  pinMode(GPIOA, ANALOG); // Set GPIOA to Analog mode
  pinMode(GPIOB, ANALOG); // Set GPIOB to Analog mode
  pinMode(GPIOC, ANALOG); // Set GPIOC to Analog mode
  pinMode(GPIOD, ANALOG); // Set GPIOD to Analog mode
}
// Loop program
void loop() {
  // NOTE: RoboBoard revision v1.1 GPIOB pin does not support analog input
  //       (analogRead()) functionality. But can be used with analogWrite().
  //       Trying to call analogRead(GPIOB) will print an error.
  // Read analog value of GPIO pins
  // Will return value between 0-4095
  int gpioA = analogRead(GPIOA);
  int gpioB = X4.getRevisionNum() == 10 ? analogRead(GPIOB) : 0;
  int gpioC = analogRead(GPIOC);
  int gpioD = analogRead(GPIOD);
  // Measure approximate input voltage of GPIO pins (millivolts)
  // Will return value between 0-3300
  float gpioAmV = analogReadMilliVolts(GPIOA);
  float gpioBmV = X4.getRevisionNum() == 10 ? analogReadMilliVolts(GPIOB) : 0;
  float gpioCmV = analogReadMilliVolts(GPIOC);
  float gpioDmV = analogReadMilliVolts(GPIOD);
  // Convert millivolts to Volts (3123 -> 3.123)
  float gpioAVolt = gpioAmV / 1000;
  float gpioBVolt = gpioBmV / 1000;
  float gpioCVolt = gpioCmV / 1000;
  float gpioDVolt = gpioDmV / 1000;
  // Print GPIO pin values
  Serial.printf("GPIO A: %4d(%.3fV), B: %4d(%.3fV), C: %4d(%.3fV), D: %4d(%.3fV)\n",
    gpioA, gpioAVolt,
    gpioB, gpioBVolt,
    gpioC, gpioCVolt,
    gpioD, gpioDVolt
    );
  // Wait for 100 milliseconds
  delay(100);
}