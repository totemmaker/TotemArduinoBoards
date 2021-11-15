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
void loopPositionRead() {
  // Print current servo motor position
  Serial.printf("Pos: %4d%%, Angle: %3d, Pulse: %4dus\n", 
    X4.servoA.getPos(), 
    X4.servoA.getAngle(), 
    X4.servoA.getPulse()
  );
  delay(100);
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Start parallel loop to print current motor position
  addLoop(loopPositionRead);
}
// Loop program
void loop() {
  // Simple motor spin
  X4.servoA.angle(0); // Spin motor to angle 0 (degree)
  delay(500);
  X4.servoA.angle(90); // Spin motor to angle 90 (degree)
  delay(1000);
  // Inverted direction motor spin
  X4.servoA.setInvert(true); // Enable motor spin to opposite direction
  X4.servoA.angle(0);
  delay(500);
  X4.servoA.angle(90);
  delay(500);
  X4.servoA.setInvert(false); // Disable direction switching
  // Set custom RPM speed for positioning.
  // Maximum speed is determined by motor capabilities.
  // Typically it's around ~60rpm.
  // When speed is set, getPos() function will return exact motor
  // position at the moment.
  X4.servoA.setSpeed(10); // Set motor spin speed to 10rpm
  X4.servoA.angle(0);
  delay(2500);
  X4.servoA.angle(90);
  delay(2500);
  X4.servoA.setSpeed(0); // Set back to maximum motor speed
  // Spin for specified length of time.
  // This function will spin motor at speed required to reach
  // specified position at given time.
  X4.servoA.angle(0, 2000); // Spin to position 0 in 2 seconds
  delay(2500);
  X4.servoA.angle(90, 1000); // Spin to position 90 in 1 second
  delay(1500);
}