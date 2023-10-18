#include <Arduino.h>
/*
  Setup RoboCar to use Drivetrain module.
  Allows to configure robot wheel placement and use
  functions to control drive direction.
*/
// Initialize program
void setup() {
  /**
   * Steer drive configuration
   */
  // Assign left wheel to DC motor port A
  Drivetrain.setWheelLeft(DC.A);
  // Assign right wheel to DC motor port B
  Drivetrain.setWheelRight(DC.B);
  // Select steer drive
  Drivetrain.setDriveSteer();
  // Invert steering spin direction
  Servo.A.setInvert(true);
  // Trim steering correct angles and range
  Servo.A.setTrim(-38, -7, 18);
  // Wait for USB cable to be pulled out
  Board.waitUSB();
  // Wait for button press to start driving
  Button.waitClick();
}
// Loop program
void loop() {
  // Drive straight at 40% speed
  Drivetrain.drive(40);
  delay(1000); // Wait 1 second
  // Drive backward at 40% speed
  Drivetrain.drive(-40);
  delay(1000); // Wait 1 second
  // Brake to full stop
  Drivetrain.brake();
  delay(1000); // Wait 1 second
  // Drive left
  Drivetrain.driveTurn(40, -100);
  delay(1000); // Wait 1 second
  // Drive right
  Drivetrain.driveTurn(40, 100);
  delay(2000); // Wait 2 second
  // Brake to full stop
  Drivetrain.brake();
  delay(1000); // Wait 1 second
}
