#include <Arduino.h>
/*
  Blink RoboBoard LED at different intervals with
  separate loop functions.
  Example of "addLoop()" functionality.
*/
// (additional) Loop program
void loopLedA() { // Blink RGB A at 1s rate
    RGB.A.toggle();
    delay(1000);
}
// (additional) Loop program
void loopLedB() { // Blink RGB B at 0.5s rate
    RGB.B.toggle();
    delay(500);
}
// (additional) Loop program
void loopLedC() { // Blink RGB C at 0.25s rate
    RGB.C.toggle();
    delay(250);
}
// Initialize program
void setup() {
    // Change LED colors
    RGB.A.color(Color::Red);
    RGB.B.color(Color::Green);
    RGB.C.color(Color::Blue);
    RGB.D.color(Color::White);
    // Create additional loops
    addLoop(loopLedA);
    addLoop(loopLedB);
    addLoop(loopLedC);
}
// (main) Loop program
void loop() { // Blink RGB D at 0.1s rate
    RGB.D.toggle();
    delay(100);
}
