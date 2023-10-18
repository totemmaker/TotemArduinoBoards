#include <Arduino.h>
/*
  RoboBoard example to configure DC output frequency.

  PWM (Pulse-width modulation) is used to control motor power.
  When setting DC.spin(30) a signal is generated where it
  spends 30% of time in "on" position and rest in "off" position.
  This signal is repeated at 50Hz frequency (every 20ms).
  Using this technique, motor will receive only 30% of available power
  as a result it will spin slower (less torque).
  For RoboBoard X3 it's configured as 20000Hz PWM in slow decay mode.
  For RoboBoard X4 it's configured as 50Hz PWM in fast decay mode (will change in future).
  Typically, 20kHz slow decay mode is best for motors (providing linear speed control)
  and should be changed only if specific use case requires so.

               Frequency:
HIGH|         <-- 50Hz -->         |
    |__________                    |
    |    on    |       off         |
    |   30 %   |      70 %         |
    |          |___________________|
 LOW|        30% duty cycle        |
*/
// Initialize program
void setup() {
  DC.spin(30); // Set duty cycle to 30%
}
// Loop program
void loop() {
  DC.setFrequency(50); // Set frequency to 50Hz
  delay(2000); // Wait 2 seconds
  DC.setFrequency(1000); // Set frequency to 1000Hz
  delay(2000); // Wait 2 seconds
  DC.setFrequency(20000); // Set frequency to 20000Hz
  delay(2000); // Wait 2 seconds
  // You can see how motor response changes with different frequency
}