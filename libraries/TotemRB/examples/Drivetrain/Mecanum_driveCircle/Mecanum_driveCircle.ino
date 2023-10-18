#include <Arduino.h>
/*
  Example to drive Mecanum robot in a circle.
  Press a button to start driving
*/
// Initialize program
void setup() {
  /**
   * Mecanum drive configuration
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
  // Limit maximum speed if required
  // Drivetrain.setMaxSpeed(50);
  // Wait for button click to start driving
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
  // Loop 0-359 degrees
  for (int deg=0; deg<360; deg+=5) {
    // Update drivetrain move direction
    Drivetrain.driveDirection(100, deg);
    delay(35); // Wait 35ms
  }
}
