#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to read functionX click on mobile App.
           Use this functionality to make X4 perform specific actions
           on button press inside App.

  Note: In mobile App you can create a widget pointing to functionA,
        functionB, functionC or functionD. When button is clicked, value
        is sent to X4 and can be read using this example.
*/
// Event function called when widget on app is clicked
void eventFunctionA() {
  Serial.print("FunctionA: ");
  Serial.println(X4.functionA.get());
}
void eventFunctionB() {
  Serial.print("FunctionB: ");
  Serial.println(X4.functionB.get());
}
void eventFunctionC() {
  Serial.print("FunctionC: ");
  Serial.println(X4.functionC.get());
}
void eventFunctionD() {
  Serial.print("FunctionD: ");
  Serial.println(X4.functionD.get());
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Enable App connectivity (will override Tools -> App control -> Disabled)
  X4.enableAppControl();
  // Register event for each function
  X4.functionA.addEvent(eventFunctionA);
  X4.functionB.addEvent(eventFunctionB);
  X4.functionC.addEvent(eventFunctionC);
  X4.functionD.addEvent(eventFunctionD);
}
// Loop program
void loop() {
  // Empty
}