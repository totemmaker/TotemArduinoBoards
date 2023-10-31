#include <Arduino.h>
/*
  Example to manually control motors attached to robot wheels.
  For more simplicity, it is recommended to use "Drivetrain" library.
*/
// Create alias name to DC.A and DC.B port control
auto &wheelLeft = DC.A;
auto &wheelRight = DC.B;
// Can also write:
// DC.A.spin(50);
// DC.B.spin(50);
// Initialize program
void setup() {
  // Flip left wheel spin direction
  wheelLeft.setInvert(true);
}
// Loop program
void loop() {
  // Drive straight at 50%
  wheelLeft.spin(50);
  wheelRight.spin(50);
  delay(1000);
  // Turn right
  wheelLeft.spin(50);
  wheelRight.brake();
  delay(500);
  // Stop driving
  wheelLeft.brake();
  wheelLeft.brake();
  delay(500);
  // Drive backwards at 50%
  wheelLeft.spin(-50);
  wheelRight.spin(-50);
  delay(1000);
  // Turn left
  wheelLeft.spin(50);
  wheelRight.brake();
  delay(500);
  // Stop driving
  wheelLeft.brake();
  wheelLeft.brake();
  delay(1000);
}