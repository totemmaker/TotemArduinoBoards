#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to configure DC output signal

  PWM (Pulse-width modulation) is used to control motor power.
  When setting X4.dcA.power(30) a signal is generated where it
  spends 30% of time in "on" position and rest in "off" position.
  This signal is repeated at 50Hz frequency (every 20ms).
  Using this technique, motor will receive only 30% of available power
  as a result it will spin slower (less torque).

  Typically motors work best at 50Hz, but this example shows how to modify it.
  Also, amount of total power (100% duty cycle) can be increased to add resolution for
  more precise control.

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
  // Increase power range to 0-1000.
  // This gives more fine control than 0-100
  X4.dcAB.setPowerRange(1000);
  X4.dcA.power(325); // Set duty cycle to 32.5%
}
// Loop program
void loop() {
  X4.dcAB.setFreq(50); // Set frequency to 50Hz (default)
  delay(2000);
  X4.dcAB.setFreq(1000); // Set frequency to 1000Hz
  // You can see how motor response becomes worse with higher frequency
  delay(2000);
}