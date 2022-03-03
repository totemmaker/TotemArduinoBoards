#include <Arduino.h>
/*
  Module:  [11] Totem Distance sensor
  Details: Example showing how to enable RGB bright mode.
           When object is not detected - displaying multi colors at max brightness
           When object is detected - displaying single color at max brightness
  
  Note: Bright mode can only be used when setting all LED to the same color.
  If different colors per LED are set - brightness will be dimmed.
  This mode disables multiplexing, giving for more
  time for each LED to emit light.
  It is disabled by default to match brightness.
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
  // Check if distance is more than 0 and less than 300 (mm)
  if (distance != 0 && distance < 300) {
    // Calculate color according to distance
    int color = map(constrain(distance, 100, 300), 100, 300, 0, 255);
    // Set all LED color (bright)
    sensor.rgb.colorRGB(chAll, 255-color, color, 0);
  }
  else {
    // Update random color per each LED
    for (int i=chA; i<8; i++) {
      sensor.rgb.colorRGB(i, rand()%255, rand()%255, rand()%255);
    }
    // Delay 100ms between color update
    delay(100);
  }
}