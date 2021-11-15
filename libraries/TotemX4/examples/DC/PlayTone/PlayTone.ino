#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to play tones using DC motor.
           Ports dcAB and dcCD can vibrate motor at specified freequency in order
           to create sound. Some melody can by played by combining multiple of tones.
           Two separate channel groups AB, CD can be controlled individually.
           Setting tone X4.dcAB.tone() will affect both channels (A and B), they can't
           be separated, unless one of them is disabled X4.dcB.disable().
           Standad Arduino function tone() will redirect to X4.dcAB.tone() so all
           Arduino "buzzer" examples are compatible.
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  /*
    Play two different tones (500Hz and 1000Hz)
  */
  X4.dcAB.tone(500); // Play 500Hz tone indefinitely
  delay(1000);
  // Standard Arduino tone(pin, frequency, duration) function is forwarded to
  // X4.dcAB.tone(frequency, duration). "pin" parameter is ignored
  tone(0, 1000); // Play 1000Hz tone indefinitely
  delay(1000);
  /*
    Beep 5 times at 800Hz
  */
  for (int i=0; i<5; i++) {
    X4.dcAB.tone(800, 100); // Play 800Hz tone for 100ms
    delay(500);
  }
  /*
    Alarm
  */
  for (int i=0; i<5; i++) {
    for (int t=100; t<1000; t+=5) {
      X4.dcAB.tone(t);
      delay(5);
    }
  }
  /*
    Tone wave
  */
  for (int t=100; t<5000; t+=5) {
    X4.dcAB.tone(t);
    delay(5);
  }
  for (int t=5000; t>=100; t-=5) {
    X4.dcAB.tone(t);
    delay(5);
  }
  X4.dcAB.tone(0); // Stop tone play
  delay(500);
}