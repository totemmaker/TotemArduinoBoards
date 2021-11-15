#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  Details: Example showing how to read knob position and button state
  
  Note: Reading values directly (sensor.knobA.get()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  If you want non-blocking code, check "Event" based example.
*/
// Initialize Potentiometer module
Module15 pot;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
}
// Loop program
void loop() {
  // Print knob & button values
  Serial.printf("Knob A: %4d B: %4d C: %4d, Button A: %d B: %d C: %d\n", 
    pot.knobA.get(), pot.knobB.get(), pot.knobC.get(),
    pot.buttonA.isPressed(), pot.buttonB.isPressed(), pot.buttonC.isPressed()
  );
  // Delay printing
  delay(50);
}