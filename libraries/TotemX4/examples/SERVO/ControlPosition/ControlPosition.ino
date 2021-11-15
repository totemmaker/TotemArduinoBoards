#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to control Servo motor position

  PWM (Pulse-width modulation) is used to control servo motor position.
  When setting X4.servoA.angle(90) a signal is generated where it goes
  LOW after 1500us (microsecond) and goes up after 18.5ms (millisecond).
  Using these timings, servo motor knows position it should spin to.

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
  X4.servoA.pos(-100); // Spin to angle 0
  delay(2000);
  X4.servoA.pos(0); // Spin to angle 90 (center)
  delay(1000);
  X4.servoA.pos(100); // Spin to angle 180
  delay(1000);
  // Angle control [0:180]
  X4.servoA.angle(0); // Spin to angle 0
  delay(2000);
  X4.servoA.angle(90); // Spin to angle 90 (center)
  delay(1000);
  X4.servoA.angle(180); // Spin to angle 180
  delay(1000);
  // Pulse (microseconds) control [500:2500]
  X4.servoA.pulse(500); // Spin to angle 0
  delay(2000);
  X4.servoA.pulse(1500); // Spin to angle 90 (center)
  delay(1000);
  X4.servoA.pulse(2500); // Spin to angle 180
  delay(1000);
}