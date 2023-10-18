#include <Arduino.h>
/*
  Example of using Button library to read current button state.
  Functions "is" returns true until state changes.
  In RoboBoard X3 button is named "BOOT".
  In RoboBoard X4 button is named "BUTTON".
*/
// Initialize program
void setup() {
  Serial.begin(115200);
}
// Loop program
void loop() {
  if (Button.isPressedFor(1000)) { // is held pressed for 1 second
    Serial.println("Press for 1000ms");
  }
  else if (Button.isPressed()) { // button is pressed
    Serial.println("Press");
  }
  else if (Button.isReleased()) { // button is released
    Serial.println("Release");
  }
  delay(250);
}
