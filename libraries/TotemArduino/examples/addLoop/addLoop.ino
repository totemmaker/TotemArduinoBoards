#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to create parallel loop functions (multithreading).
           Each loop runs independently and delay() does not affect each other.
           Counter variables will be incremented at different rate.
           Run Serial Monitor at 9600 speed to view 
           Serial print output.
*/
// Variables to hold count for each loop
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;
// Arduino loop (default)
void loop() {
  // Print loop counters
  Serial.printf("%08lu: loop2: %3d, loop3: %3d, loop4: %3d\n",
    millis(), counter2, counter3, counter4);
  // Delay printing for 100ms
  delay(100);
}
// Loop 2 function
void loop2() {
  counter2++; // Increment counter
  delay(100); // Delay counting to 100ms
}
// Loop 3 function
void loop3() {
  counter3++; // Increment counter
  delay(500); // Delay counting to 500ms
}
// Loop 4 function
void loop4() {
  counter4++;  // Increment counter
  delay(1000); // Delay counting to 1000ms
}
// Arduino setup
void setup() {
  // Start serial communication
  Serial.begin(9600);
  addLoop(loop2); // Start parallel loop2
  addLoop(loop3); // Start parallel loop3
  addLoop(loop4); // Start parallel loop4
}
