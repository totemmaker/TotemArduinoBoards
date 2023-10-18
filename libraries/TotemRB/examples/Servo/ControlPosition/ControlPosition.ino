#include <Arduino.h>
/*
  RoboBoard example to control Servo motor position

  PWM (Pulse-width modulation) is used to control servo motor position.
  When setting Servo.spinAngle(90) a signal is generated where it goes
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
  // Position control [-100:100]
  RGB.color(Color::Green);
  Servo.spinPos(-100); // Spin to angle 0
  delay(2000);
  Servo.spinPos(0); // Spin to angle 90 (center)
  delay(1000);
  Servo.spinPos(100); // Spin to angle 180
  delay(1000);
  // Angle control [0:180]
  RGB.color(Color::Yellow);
  Servo.spinAngle(0); // Spin to angle 0
  delay(2000);
  Servo.spinAngle(90); // Spin to angle 90 (center)
  delay(1000);
  Servo.spinAngle(180); // Spin to angle 180
  delay(1000);
  // Pulse (microseconds) control [500:2500]
  RGB.color(Color::Blue);
  Servo.spinPulse(500); // Spin to angle 0
  delay(2000);
  Servo.spinPulse(1500); // Spin to angle 90 (center)
  delay(1000);
  Servo.spinPulse(2500); // Spin to angle 180
  delay(1000);
}