#include <Arduino.h>
/*
  Example displaying how to use Servo library to steer RoboCar front wheels.
  Servo motor should be connected to Servo port A.
*/
// Initialize program
void setup() {
  // Invert steering spin direction
  Servo.A.setInvert(true);
  // Trim steering correct angles and range
  // Maximum to left: -38%
  // Center position: -7%
  // Maximum to right: 18%
  Servo.A.setTrim(-38, -7, 18);
}
// Loop program
void loop() {
  // Steer to right
  Servo.A.spinPos(100);
  delay(1000);
  // Steer to center
  Servo.A.spinPos(0);
  delay(1000);
  // Steer to left
  Servo.A.spinPos(-100);
  delay(1000);
  // Slow steer
  for (int i=-100; i<100; i+=5) { // From left to right
    Servo.A.spinPos(i);
    delay(60);
  }
  for (int i=100; i>0; i-=5) { // From right to center
    Servo.A.spinPos(i);
    delay(60);
  }
  delay(1000);
}
