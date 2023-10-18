#include <Arduino.h>
/*
  RoboBoard example to use servo motor sequencing.
  These sequences can be run anytime asynchronously.
*/
// Prepare movement sequence
// delay - ms to wait before applying position
// position - motor position [-100:100]
// Maximum number of steps - 6
ServoSequence sequence1[] = {
  {500, -50},
  {500, 0},
};
ServoSequence sequence2[] = {
  {500, 50},
  {500, 0},
};
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Run sequence 1 time
  RGB.color(Color::Green);
  Servo.run(sequence1); // Run configured sequence 1 time
  Servo.wait(); // Wait till sequence finishes
  delay(1000); // Wait 1 second
  // Run sequence 2 times
  RGB.color(Color::Red);
  Servo.run(sequence2, 2); // setting 0 would run indefinitely
  Servo.wait(); // Wait till sequence finishes
  delay(1000); // Wait 1 second
}
