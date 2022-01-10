#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to enable RGB bright mode.
  
  Note: Bright mode can only be used to set all LED at the same color.
  If different colors per LED are required - module will switch to
  standard mode. This mode disables multiplexing, allowing for more
  time for LED to emit light.
*/
// Initialize Distance sensor
Module11 sensor;
// Initialize program
void setup() {
  // Enable bright mode
  sensor.rgb.setBrightMode(true);
}
// Loop program
void loop() {
  // Read distance
  int distance = sensor.distance.getMM();
  // Check if distance is more than 0 and less than 500 (mm)
  if (distance != 0 && distance < 500) {
    // Calculate color according to distance
    int color = map(constrain(distance, 100, 500), 100, 500, 0, 255);
    // Set all LED color (bright)
    sensor.rgb.color(255-color, color, 0);
  }
  else {
    // Update random color per each LED
    for (int i=0; i<8; i++) {
      sensor.rgb.colorX(i, rand()%255, rand()%255, rand()%255);
    }
    // Delay 100ms between color update
    delay(100);
  }
}