#include <Arduino.h>
/*
  Example of using Button library to wait for button event.
  Will hold code execution until button is interacted.
  In RoboBoard X3 button is named "BOOT".
  In RoboBoard X4 button is named "BUTTON".
*/
// Initialize program
void setup() {
  Serial.begin(115200);
}
// Loop program
void loop() {
  // Wait until button is clicked
  Serial.println("Waiting for button click...");
  Button.waitClick();
  Serial.println("-> Button was clicked");
  // Wait until button is double clicked
  Serial.println("Waiting for button double click...");
  Button.waitDoubleClick();
  Serial.println("-> Button was double clicked");
  // Wait until button is long pressed
  Serial.println("Waiting for button long press...");
  Button.waitLongPress();
  Serial.println("-> Button was long pressed");
  // Wait until button is clicked (timeout after 2 seconds)
  Serial.println("Waiting for button click (with timeout)...");
  if (Button.waitClick(3000)) {
    Serial.println("-> Button was clicked (before timeout)");
  }
  else {
    Serial.println("-> Button click timeout (3s)");
  }
}
