#include <Arduino.h>
/*
  RoboBoard example to play tones using DC motor.
  DC outputs can vibrate motor at specified frequency in order
  to create sound. Some melody can by played by combining multiple of tones.
  In RoboBoard X4 - ports A and B, C and D are tied together and
  can only play same frequency.
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
  DC.tone(500); // Play 500Hz tone indefinitely
  delay(1000);
  // Standard Arduino tone(pin, frequency, duration) function is forwarded to
  // DC.tone(frequency, duration). "pin" parameter is ignored
  DC.tone(1000); // Play 1000Hz tone indefinitely
  delay(1000);
  /*
    Beep 5 times at 800Hz
  */
  for (int i=0; i<5; i++) {
    DC.tone(800, 100); // Play 800Hz tone for 100ms
    delay(100);
    // RoboBoard X3 does not support tone duration at the moment
    // Stop it manually
    if (Board.getNumber() == 3) DC.tone(0);
    delay(400);
  }
  /*
    Alarm
  */
  for (int i=0; i<5; i++) {
    for (int t=100; t<1000; t+=5) {
      DC.tone(t);
      delay(5);
    }
  }
  /*
    Tone wave
  */
  for (int t=100; t<5000; t+=5) {
    DC.tone(t);
    delay(5);
  }
  for (int t=5000; t>=100; t-=5) {
    DC.tone(t);
    delay(5);
  }
  DC.tone(0); // Stop tone play
  delay(500);
}
