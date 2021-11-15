#include <Arduino.h>
/*
  Board:  [X4] RoboBoard X4
  Details: Example how to read RoboBoard X4 stored configuration.
           You can connect App to change these settings and see them
           displayed here
*/
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Enable App connectivity (will override Tools -> App control -> Disabled)
  X4.enableAppControl();
}
// Loop program
void loop() {
  // Print robot info
  Serial.println();
  Serial.printf("Robot:\n"
  "  - name: %s\n"
  "  - color: %6X (HEX)\n"
  "  - model: %x (hash)\n",
  X4.config.getRobotName(),
  X4.config.getRobotColor(),
  X4.config.getRobotModel()
  );
  // Print DC ports info
  Serial.printf("Inverted: dcA: %s, dcB: %s, dcC: %s, dcD: %s\n",
    X4.config.getDCInvert()&0xFF000000 ? "Yes" : "No",
    X4.config.getDCInvert()&0x00FF0000 ? "Yes" : "No",
    X4.config.getDCInvert()&0x0000FF00 ? "Yes" : "No",
    X4.config.getDCInvert()&0x000000FF ? "Yes" : "No"
  );
  // Print DC ports info
  Serial.printf("Autobrake: dcA: %d%%, dcB: %d%%, dcC: %d%%, dcD: %d%%\n",
    (X4.config.getDCAutobrake() >> 24) & 0xFF,
    (X4.config.getDCAutobrake() >> 16) & 0xFF,
    (X4.config.getDCAutobrake() >> 8)  & 0xFF,
    (X4.config.getDCAutobrake())       & 0xFF
  );
  // Delay 3 seconds
  delay(3000);
}