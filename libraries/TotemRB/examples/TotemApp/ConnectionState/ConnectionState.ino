#include <Arduino.h>
/*
  RoboBoard example to use Totem App connection control.
  1. Run this sketch. Connect Serial Monitor
  3. Connect with Totem App
  4. Press RoboBoard button to force disconnect
*/
void onButtonEvent(int evt) {
  // Force to disconnect Totem App on button press
  if (evt == Button.evtPress) {
    Serial.println("Force disconnect 'TotemApp.disconnect()'");
    TotemApp.disconnect();
  }
}
void onAppEvent(int evt, int value) {
  if (evt == TotemApp.evtConnect)
    Serial.println("Totem App connected");
  else if (evt == TotemApp.evtDisconnect)
    Serial.println("Totem App disconnected");
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register Totem App event function
  TotemApp.addEvent(onAppEvent);
  // App connectivity is started internally by "TotemApp.addEvent()"
  // Register RoboBoard button event function
  Button.addEvent(onButtonEvent);
  // Wait until Totem App is connected
  while (!TotemApp.wait(1500)) { // Wait 1.5 sec until timeout
    Serial.println("Waiting for app to connect...");
  }
  Serial.println("Wait exit. Running program...");
}
// Loop program
void loop() {
  // Empty
}