#include <Arduino.h>
/*
  Example of using Button library to read previous button events.
  Functions "was" returns true only single time after button event.
  Convenient to use inside loop().
  In RoboBoard X3 button is named "BOOT".
  In RoboBoard X4 button is named "BUTTON".
*/
// Initialize program
void setup() {
  Serial.begin(115200);
}
// Loop program
void loop() {
  if (Button.wasPressed()) { // on button press
    Serial.println("Press");
  }
  if (Button.wasReleased()) { // on button release
    Serial.println("Release");
  }
  if (Button.wasClick()) { // on button click (fast press and release)
    Serial.println("Click");
  }
  if (Button.wasLongPress()) { // on long press (500ms)
    Serial.println("LongPress");
  }
  if (Button.wasDoubleClick()) { // on double click
    Serial.println("DoubleClick");
  }
}
