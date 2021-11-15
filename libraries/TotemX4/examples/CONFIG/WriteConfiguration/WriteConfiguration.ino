#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to write RoboBoard X4 stored configuration.
           Press BUTTON to set random Robot color and click RESET
           to restart X4 and check how it boots with configured color
*/
// Initialize program
void setup() {
  // Empty
}
// Loop program
void loop() {
  // Wait for button press
  if (X4.button.wasPressed()) {
    // Generate HEX with random RGB color (0xFFFFFF)
    int newColor = (rand() % 255) << 16 | (rand() % 255) << 8 | (rand() % 255);
    // Update RGB LED to display generated color
    X4.rgb.color(255, newColor); // Brightness, RGB HEX (0xFFFFFF)
    // Save color to configuration storage
    X4.config.setRobotColor(newColor);
    // After pressing RESET, X4 will reboot and use configured RGB color
    // Also will display this color when connecting to mobile app
  }
}