#include <Arduino.h>
/*
  RoboBoard example to configure DC output frequency.

  PWM (Pulse-width modulation) is used to control motor power.
  When setting DC.spin(30) a signal is generated where it
  spends 30% of time in "on" position and rest in "off" position.
  This signal is repeated at 20kHz frequency.
  Using this technique, motor will receive only 30% of available power
  as a result it will spin slower (less torque).
  Decay modes changes behavior of the motor:
  Slow decay - linear speed control, rapid speed change.
  Fast decay - torque control, free spinning.
  Typically, 20kHz slow decay mode is best for motors.
  Settings should be changed only if specific use case requires so.

               Frequency:
HIGH|         <-- 20kHz -->        |
    |__________                    |
    |    on    |       off         |
    |   30 %   |      70 %         |
    |          |___________________|
 LOW|        30% duty cycle        |
*/
// Initialize program
void setup() {
  Serial.begin(115200);
  DC.spin(30); // Set duty cycle to 30%
}
// Loop program
void loop() {
  // Motor spins fast and high torque
  DC.setFastDecay();
  DC.setFrequency(50); // Set frequency to 50Hz
  Serial.println("Frequency: 50Hz fast decay");
  delay(2000); // Wait 2 seconds
  // Motor spins a bit slower and low torque
  DC.setFastDecay();
  DC.setFrequency(1000); // Set frequency to 1000Hz
  Serial.println("Frequency: 1kHz fast decay");
  delay(2000); // Wait 2 seconds
  // Motor spins very slow and average torque
  DC.setSlowDecay();
  DC.setFrequency(20000); // Set frequency to 20000Hz
  Serial.println("Frequency: 20kHz slow decay");
  delay(2000); // Wait 2 seconds
  // You can see how motor response changes with different settings
}
