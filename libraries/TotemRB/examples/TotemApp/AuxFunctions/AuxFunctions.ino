#include <Arduino.h>
/*
  RoboBoard example to read functionX click on mobile App.
  Use this functionality to make RoboBoard perform specific actions
  on button press inside Totem App.

  Note: In mobile App you can create a widget pointing to functionA,
  functionB, functionC or functionD. When button is clicked, value
  is sent to RoboBoard and can be read using this example.
*/
// Event function called when widget on app is clicked
void onAppEvent(int evt, int value) {
  if (evt == TotemApp.evtConnect)
    Serial.println("Totem App connected");
  if (evt == TotemApp.evtDisconnect)
    Serial.println("Totem App disconnected");
  if (evt == TotemApp.evtFunctionA)
    Serial.printf("FunctionA: %d\n", value);
  if (evt == TotemApp.evtFunctionB)
    Serial.printf("FunctionB: %d\n", value);
  if (evt == TotemApp.evtFunctionC)
    Serial.printf("FunctionC: %d\n", value);
  if (evt == TotemApp.evtFunctionD)
    Serial.printf("FunctionD: %d\n", value);
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register Totem App event function
  TotemApp.addEvent(onAppEvent);
  // App connectivity is started internally by "TotemApp.addEvent()"
}
// Loop program
void loop() {
  // Empty
}