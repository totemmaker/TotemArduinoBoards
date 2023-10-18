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
  // Spin left track at 15% forward, right at 70% forward
  Drivetrain.spinLeftRight(15, 70);
  delay(1000); // Wait 1 second
  // Spin left track at 30% forward, right at 30% forward
  Drivetrain.spinLeftRight(30, 30);
  delay(1000); // Wait 1 second
  // Spin left track at 100% backward, right at 100% forward
  Drivetrain.spinLeftRight(-100, 100);
  delay(1000); // Wait 1 second
  // Brake to full stop
  Drivetrain.brake();
  delay(1000); // Wait 1 second
}
