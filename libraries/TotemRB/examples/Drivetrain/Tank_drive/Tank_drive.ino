#include <Arduino.h>
/*
  Setup RoboBoard to use Drivetrain module.
  Allows to configure robot wheel placement and use
  functions to control drive direction.
*/
// Initialize program
void setup() {
  /**
   * Tank drive configuration
   */
  // Assign left wheel to DC motor port A
  Drivetrain.setWheelLeft(DC.A);
  // Assign right wheel to DC motor port B
  Drivetrain.setWheelRight(DC.B);
  // Select tank drive
  Drivetrain.setDriveTank();
  // Wait for button press to start driving
  Button.waitClick();
}
// Loop program
void loop() {
  // Drive forward at 50% speed
  Drivetrain.drive(50);
  delay(1000); // Wait 1 second
  // Drive backward at 50% speed
  Drivetrain.drive(-50);
  delay(1000); // Wait 1 second
  // Turn left at 50% speed
  Drivetrain.turn(-50);
  delay(1000); // Wait 1 second
  // Turn right at 50% speed
  Drivetrain.turn(50);
  delay(1000); // Wait 1 second
  // Turn forward ant turn at 50% speed
  Drivetrain.driveTurn(50, 50);
  delay(1000); // Wait 1 second
  // Brake to full stop
  Drivetrain.brake();
  delay(1000); // Wait 1 second
}
