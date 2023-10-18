#include <Arduino.h>
/*
  Example to save board configuration to flash.
  New generated color is configured as appearance and
  loaded after processor restart.
*/
// Initialize program
void setup() {
  // Loads previously configured color
  // Wait two seconds
  delay(2000);
  // Generate random RGB color
  int color = Color::random();
  // Set new RGB appearance color
  Board.setColor(color); // RGB color on boot
  // Save new color setting to flash
  Board.settingsSave();
  // Restart processor
  Board.restart();
}
// Loop program
void loop() {
  // Empty
}