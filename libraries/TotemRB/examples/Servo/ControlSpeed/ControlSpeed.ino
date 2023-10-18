#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4 (X3 servo speed not yet supported)
  RoboBoard example to control Servo motor position

  PWM (Pulse-width modulation) is used to control servo motor position.
  When setting Servo.angle(90) a signal is generated where it goes
  LOW after 1500us (microsecond) and goes up after 18.5ms (millisecond).
  Using this timing - servo motor knows position it should spin to.

               Frequency:
HIGH|         <-- 50Hz (20ms) -->            |
    |_                                       |
    | |______________________________________|
 LOW| Period:   500us (angle 0)              |

               Frequency:
HIGH|         <-- 50Hz (20ms) -->            |
    |___                                     |
    |   |____________________________________|
 LOW| Period:  1500us (angle 90)             |

               Frequency:
HIGH|         <-- 50Hz (20ms) -->            |
    |_____                                   |
    |     |__________________________________|
 LOW| Period:  2500us (angle 180)            |

*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Simple motor spin (max speed)
  RGB.color(Color::Red);
  Servo.setSpeedRPM(0); // Set back to maximum motor speed
  Servo.spinAngle(90); // Spin motor to angle 90 (degree)
  delay(500);
  Servo.spinAngle(0); // Spin motor to angle 0 (degree)
  delay(1000);
  // Set custom RPM speed for positioning.
  // Maximum speed is determined by motor capabilities.
  // Typically it's around ~60rpm.
  RGB.color(Color::Green);
  Servo.setSpeedRPM(10); // Set motor spin speed to 10rpm
  Servo.spinAngle(90);
  delay(2500);
  Servo.spinAngle(0);
  delay(2500);
  // Spin for specified length of time.
  // This function will spin motor at speed required to reach
  // specified position at given time.
  // Also overrides setSpeedRPM() setting
  RGB.color(Color::Blue);
  Servo.spinAngleDuration(90, 500); // Spin to position 90 in 1 second
  delay(500);
  Servo.spinAngleDuration(0, 2000); // Spin to position 0 in 2 seconds
  Servo.wait();
  delay(1000);
}
