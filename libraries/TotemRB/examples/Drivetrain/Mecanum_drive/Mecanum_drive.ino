#include <Arduino.h>
/*
  Setup RoboBoard to use Drivetrain module.
  Allows to configure robot wheel placement and use
  functions to control drive direction.

  To start driving - press a button.
*/
// Initialize program
void setup() {
  /**
   * Mecanum drive configuration
   * NOTE: motor spin direction (invert) has to be set
   * correctly in order for Drivetrain logic to work.
   */
  // Assign left front wheel to DC motor port A
  Drivetrain.setWheelLeftFront(DC.A, true);
  // Assign right front wheel to DC motor port B
  Drivetrain.setWheelRightFront(DC.B, true);
  // Assign left rear wheel to DC motor port C
  Drivetrain.setWheelLeftRear(DC.C, true);
  // Assign right rear wheel to DC motor port D
  Drivetrain.setWheelRightRear(DC.D, true);
  // Select mecanum drive
  Drivetrain.setDriveMecanum();
  // Limit DC motor output for 6V yellow motors
  // DC.setRange(10, 30);
  // Limit maximum robot speed
  // Drivetrain.setMaxSpeed(50);
  // Enable autobrake (when power set to 0)
  DC.setAutobrake(true);
  // Wait for button press to start driving
  Button.waitClick();
}
// Drive angles (like clock or compass)
// Forward - 0deg. Backward - 180deg.
// Left - 270deg. Right - 90deg.
//          0
//     330  |  30
//   300    |     60
// 270 -----|-----  90
//   240    |    120
//     210  |  150
//         180
// Loop program
void loop() {
  // Drive forward at 50% speed
  Drivetrain.drive(50);
  delay(1000); // Wait 1 second
  // Drive backward at 50% speed
  Drivetrain.drive(-50);
  delay(1000); // Wait 1 second
  // Drive right side at 50% speed
  Drivetrain.driveDirection(50, 60);
  delay(1500); // Wait 1.5 second
  // Drive left side at 50% speed
  Drivetrain.driveDirection(50, 270);
  delay(1500); // Wait 1.5 second
  // Drive at 50% speed to 210deg angle
  Drivetrain.driveDirection(50, 210);
  delay(1000); // Wait 1 second
  // Drive at 50% speed to 30deg angle
  Drivetrain.driveDirection(50, 30);
  delay(1000); // Wait 1 second
  // Turn left at 50% speed
  Drivetrain.turn(-50);
  delay(1000); // Wait 1 second
  // Brake to full stop
  Drivetrain.brake();
  delay(1000); // Wait 1 second
}
