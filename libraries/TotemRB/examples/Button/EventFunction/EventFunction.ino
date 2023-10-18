#include <Arduino.h>
/*
  Example of using Button library to receive interaction events.
  In RoboBoard X3 button is named "BOOT".
  In RoboBoard X4 button is named "BUTTON".
*/
// Button function called on certain event
void onButton(int evt) {
  if (evt == Button.evtPress) { // on button press
    Serial.println("Press");
  }
  else if (evt == Button.evtRelease) { // on button release
    Serial.println("Release");
  }
  else if (evt == Button.evtClick) { // on button click (fast press and release)
    Serial.println("Click");
  }
  else if (evt == Button.evtLongPress) { // on long press (500ms)
    Serial.println("LongPress");
  }
  else if (evt == Button.evtDoubleClick) { // on double click
    Serial.println("DoubleClick");
  }
}
// Initialize program
void setup() {
  Serial.begin(115200);
  // Register "onButton" function to receive button events
  Button.addEvent(onButton);
}
// Loop program
void loop() {
  // Empty
}
