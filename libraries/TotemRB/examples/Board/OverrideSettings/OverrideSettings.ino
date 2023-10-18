#include <Arduino.h>
/*
  This example will override any default or saved Board setting.
  Can be used to force some configuration values before Board initialization.
*/
// Function called after loading configuration from memory
// and before system is initialized (with loaded configuration)
// Note: if "initRoboBoard()" is used - overrides board parameters
// set in Arduino IDE Tools menu.
void initRoboBoard() {
#if ROBOBOARD_X3
  // Set RoboBoard X3 3V3 LDO regulator
  // Note: always enabled "true" by default.
  Board.setEnable3V3(true);
  // Set RoboBoard X3 charging mode
  // Powers off the board and displays RGB charging animation
  // when USB cable is plugged in
  Board.setChargingMode(false);
#endif
  // Enable board status indication with RGB LED
  // - displays battery state on power on
  // - blink red if restarted due low battery
  // - displays Totem App connection state
  Board.setStatusRGB(true);
  // Enable board status indication with motor beep sounds
  // - beep when board is powered up
  // - beep on Totem App connect / disconnect
  Board.setStatusSound(true);
}
// Initialize program
void setup() {
  // Uncomment to use TotemApp indications
  // TotemApp.begin();
}
// Loop program
void loop() {

}
