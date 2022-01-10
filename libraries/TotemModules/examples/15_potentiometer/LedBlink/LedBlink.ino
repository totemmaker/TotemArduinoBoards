#include <Arduino.h>
/*
  Module:  [15] Totem Potentiometer module
  Details: Example showing how to control LED
  
  Note: By default 3 on-board LED displays position of knob.
  This functionality can be disabled when some custom action is set
  to pot.led. Use pot.led.reset() to restore default functionality
  during runtime.
*/
// Initialize Potentiometer module
Module15 pot;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Play some LED animations
  /*
    Loading
  */
  pot.led.setAlpha(255); // Reset all LED brightness
  pot.led.off(); // Turn all LED off
  for (int c=0; c<4; c++) {
    for (int i=0; i<3; i++) {
      pot.led.onX(i); // Turn on single LED (A, B or C)
      delay(200);  
    }
    for (int i=0; i<3; i++) {
      pot.led.offX(i); // Turn off single LED (A, B or C)
      delay(200);  
    }
  }
  /*
    Pulsing
  */
  uint8_t alpha = 255;
  int timeout = millis() + 3000;
  while (millis() < timeout) {
    for (int i=0; i<3; i++) {
      pot.led.setAlphaX(i, alpha); // Change single LED brightness (A, B or C)
      alpha += 15;
    }
    delay(100);
  }
  /*
    Fade Loading
  */
  pot.led.off(); // Turn all LED off
  for (int t=0; t<3; t++) {
    for (int i=0; i<3; i++) {
      for (int c=0; c<240; c+=30) {
        pot.led.setAlphaX(i, c); // Change single LED brightness (A, B or C)
        delay(50);
      }
    }
    for (int i=2; i>=0; i--) {
      for (int c=240; c>=0; c-=30) {
        pot.led.setAlphaX(i, c); // Change single LED brightness (A, B or C)
        delay(50);
      }
    }
  }
  /*
    Fade individual
  */
  pot.led.off(); // Turn all LED off
  for (int t=0; t<2; t++) {
    for (int i=0; i<3; i++) {
      for (int c=0; c<=255; c+=5) {
        pot.led.setAlphaX(i, c); // Change single LED brightness (A, B or C)
        delay(10);
      }
      for (int c=255; c>=0; c-=5) {
        pot.led.setAlphaX(i, c); // Change single LED brightness (A, B or C)
        delay(10);
      }
    }
  }
  /*
    Binary counter
  */
  pot.led.setAlpha(255); // Reset all LED brightness
  pot.led.off(); // Turn all LED off
  for (int c=0; c<=7; c++) {
    pot.led.setBinary(c); // Output binary value B101 -> A:on, B:off, C:on
    delay(800);
  }
}