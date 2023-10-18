#include <Arduino.h>
/*
  RoboBoard example to demonstrate servo position limits.
  Allows to configure range motor should operate in.
  Convenient to use with RoboCar steering as servo, when
  wheels position is not linear.
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Position control [-100:100]
  RGB.color(Color::Green);
  // Set to operate servo in -90:10 range only. Center at -40
  Servo.A.setTrim(-90, -40, 10);
  for (int i=0; i<3; i++) { // Run 3 times
    delay(500); Servo.A.spinPos(-100);
    delay(500); Servo.A.spinPos(0);
    delay(500); Servo.A.spinPos(100);
  }
  delay(1000);
  RGB.color(Color::Red);
  // Set to operate servo in 20:80 range only. Center at 35
  Servo.A.setTrim(20, 35, 80);
  for (int i=0; i<3; i++) { // Run 3 times
    delay(500); Servo.A.spinPos(100);
    delay(500); Servo.A.spinPos(0);
    delay(500); Servo.A.spinPos(-100);
  }
  delay(1000);
}
