#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  RoboBoard example to control Module 11 RGB LED.

  Note: LED are dim in normal mode. Check "LedBrightMode"
  example if you need more brightness.
*/
// Initialize Line Follower
TotemModule11 sensor;
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
    sensor.rgb.toggle(); // Toggle all LED (on / off)
    delay(100);
  }
  /*
    Spin
  */
  for (int c=0; c<10; c++) {
    for (int i=0; i<8; i++) {
      sensor.rgb.off(); // Turn all LED off
      sensor.rgb[i].color(Color::Green); // Set single LED color (0, 1, or ...)
      delay(50);
    }
  }
  /*
    Random colors
  */
  // Update random color per each LED
  for (int c=0; c<40; c++) {
    for (int i=0; i<8; i++) {
      sensor.rgb[i].color(random(256), random(256), random(256));
    }
    delay(100);
  }
  /*
    Spin back
  */
  for (int c=0; c<10; c++) {
    for (int i=7; i>=0; i--) {
      sensor.rgb.off();
      sensor.rgb[i].color(Color::Green);
      sensor.rgb[(i+4)%8].color(Color::Red);
      delay(50);
    }
  }
  /*
    Fade
  */
  for (int c=250; c>=0; c-=10) {
    sensor.rgb.color(c, 0, 0); // Set all LED color (0, 1, and ...)
    delay(30);
  }
  for (int c=0; c<=250; c+=10) {
    sensor.rgb.color(0, 0, c);
    delay(30);
  }
  for (int c=250; c>=0; c-=10) {
    sensor.rgb.color(0, 0, c);
    delay(30);
  }
  for (int c=0; c<=250; c+=10) {
    sensor.rgb.color(0, c, 0);
    delay(30);
  }
}