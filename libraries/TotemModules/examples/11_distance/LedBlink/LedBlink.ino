#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to use RGB LED.
  
  Note: LED are dim in normal mode. Check "LedBrightMode" example if
  you need more brightness. Only available when all LED set to same color.
*/
// Initialize Distance sensor
Module11 sensor;
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Play some LED animations
  /*
    Blink
  */
  for (int c=0; c<15; c++) {
    sensor.rgb.toggle(chAll); // Toggle all LED (on / off)
    delay(100);
  }
  /*
    Spin
  */
  for (int c=0; c<10; c++) {
    for (int i=chA; i<8; i++) {
      sensor.rgb.off(chAll); // Turn all LED off
      sensor.rgb.colorRGB(i, 0, 255, 0); // Set single LED color (0, 1, or ...)
      delay(50);
    }
  }
  /*
    Random colors
  */
  // Update random color per each LED
  for (int c=0; c<40; c++) {
    for (int i=chA; i<8; i++) {
      sensor.rgb.colorRGB(i, rand()%255, rand()%255, rand()%255);
    }
    delay(100);
  }
  /*
    Spin back
  */
  for (int c=0; c<10; c++) {
    for (int i=7; i>=chA; i--) {
      sensor.rgb.off(chAll);
      sensor.rgb.colorRGB(i, 0, 255, 0);
      sensor.rgb.colorRGB((i+4)%8, 255, 0, 0);
      delay(50);
    }
  }
  /*
    Fade
  */
  for (int c=250; c>=0; c-=10) {
    sensor.rgb.colorRGB(chAll, c, 0, 0); // Set all LED color (0, 1, and ...)
    delay(30);
  }
  for (int c=0; c<=250; c+=10) {
    sensor.rgb.colorRGB(chAll, 0, 0, c);
    delay(30);
  }
  for (int c=250; c>=0; c-=10) {
    sensor.rgb.colorRGB(chAll, 0, 0, c);
    delay(30);
  }
  for (int c=0; c<=250; c+=10) {
    sensor.rgb.colorRGB(chAll, 0, c, 0);
    delay(30);
  }
}