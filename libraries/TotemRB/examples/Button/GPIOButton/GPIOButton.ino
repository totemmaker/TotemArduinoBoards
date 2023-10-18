#include <Arduino.h>
/*
  Example of using Button library with button connected to GPIO pin.
  In RoboBoard X3 pins are IO33, IO32, IO26, SIGA, SIGB
  In RoboBoard X4 pins are GPIOA, GPIOB, GPIOC, GPIOD
*/
// Library to read button state located on the board
#if ROBOBOARD_X3
IOButton button(IO33);
#endif
#if ROBOBOARD_X4
IOButton button(GPIOA);
#endif
// Initialize program
void setup() {
  Serial.begin(115200);
}
// Loop program
void loop() {
  if (button.isPressedFor(1000)) {
    Serial.println("Press for 1000ms");
  }
  else if (button.isPressed()) { // on button press
    Serial.println("Press");
  }
  else if (button.isReleased()) { // on button release
    Serial.println("Release");
  }
  delay(250);
}
