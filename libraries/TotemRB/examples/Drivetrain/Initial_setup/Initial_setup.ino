#include <Arduino.h>
/*
  Example to setup Drivetrain wheel locations and spin direction.

  On each button press a motor will spin. Check if correct ones are spinning.

  When wheels are spinning correctly, copy "Drivetrain.setWheel" configuration to
  your code.
*/
// Initialize program
void setup() {
  Serial.begin(115200);
  // Assign left front wheel to DC motor port A
  Drivetrain.setWheelLeftFront(DC.A, true);
  // Assign right front wheel to DC motor port B
  Drivetrain.setWheelRightFront(DC.B, true);
  // Assign left rear wheel to DC motor port C
  Drivetrain.setWheelLeftRear(DC.C, true);
  // Assign right rear wheel to DC motor port D
  Drivetrain.setWheelRightRear(DC.D, true);
  // Limit speed if required
  // Drivetrain.setMaxSpeed(50);
  // Wait for button press
  while (!Button.waitClick(1000)) {
    Serial.println("Waiting for a button press...");
  }
}
// Loop program
void loop() {
  // Check Left Front wheel
  Serial.println("     ___     ");
  Serial.println("^ |-|   |-|  ");
  Serial.println("    |   |    ");
  Serial.println("  |-|___|-|  ");
  Serial.println("LEFT FRONT should spin Forward");
  Drivetrain.spinWheels(30, 0, 0, 0);
  Button.waitClick();
  Drivetrain.brake();
  // Check Right Front wheel
  Serial.println("     ___     ");
  Serial.println("  |-|   |-| ^");
  Serial.println("    |   |    ");
  Serial.println("  |-|___|-|  ");
  Serial.println("RIGHT FRONT should spin Forward");
  Drivetrain.spinWheels(0, 30, 0, 0);
  Button.waitClick();
  Drivetrain.brake();
  // Check Left Rear wheel
  Serial.println("     ___     ");
  Serial.println("  |-|   |-|  ");
  Serial.println("    |   |    ");
  Serial.println("^ |-|___|-|  ");
  Serial.println("LEFT REAR should spin Forward");
  Drivetrain.spinWheels(0, 0, 30, 0);
  Button.waitClick();
  Drivetrain.brake();
  // Check Right Rear wheel
  Serial.println("     ___     ");
  Serial.println("  |-|   |-|  ");
  Serial.println("    |   |    ");
  Serial.println("  |-|___|-| ^");
  Serial.println("RIGHT REAR should spin Forward");
  Drivetrain.spinWheels(0, 0, 0, 30);
  Button.waitClick();
  Drivetrain.brake();
  // Check Right Rear wheel
  Serial.println("     ___     ");
  Serial.println("  |-|   |-|  ");
  Serial.println("    |   |    ");
  Serial.println("  |-|___|-|  ");
  Serial.println("STOP");
  Button.waitClick();
}