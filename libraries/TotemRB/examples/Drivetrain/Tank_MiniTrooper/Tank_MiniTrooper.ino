#include <Arduino.h>
/*
  Setup RoboBoard to use Drivetrain module.
  Allows to configure robot wheel placement and use
  functions to control drive direction.

  Unplug USB cable and press BOOT button.
*/
// Set flipper position [0:100]%
void setFlipper(int pos) {
  Servo.A.spinPos(map(pos, 0, 100, -100, 100));
}
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
  // Open flipper
  setFlipper(100);
  // Wait for USB cable to be pulled out
  // Prevents start driving
  Board.waitUSB();
  // Wait for button press
  Button.waitClick();
  // Wait a bit after button press
  delay(500);
  // Semi close flipper
  setFlipper(50);
}
// Loop program
void loop() {
  // Drive forward and turn right
  Drivetrain.driveTurn(50, 60);
  delay(1000); // Wait 1 second
  // Drive backward at 50% speed
  Drivetrain.drive(-50);
  delay(1000); // Wait 1 second
  // Spin in place left
  Drivetrain.turn(-100);
  delay(1000); // Wait 1 second
  // Brake to full stop
  Drivetrain.brake();
  setFlipper(100); // Open flipper
  delay(300);
  setFlipper(50); // Semi close flipper
  delay(500);
}
