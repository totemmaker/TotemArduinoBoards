#include <Arduino.h>
/*
  RoboBoard has predefined control functions like: Battery, Board, Button, CAN, RGB, ...
  These are globally defined objects for easy access without require for including libraries.
  
  Some third-party Arduino libraries may define variables with same name (like "RGB") and this
  will result in compile errors. This example demonstrates how to resolve this:

  PlatformIO: In platformio.ini add: build_flags = -DREQUIRE_TOTEM_PREFIX
  Arduino IDE: Select Tools -> Totem Prefix -> totem::Board

  Now all the functions (Board, CAN, RGB, ...) has to use "totem::" prefix (C++ namespace).
  totem::Board, totem::CAN, totem::RGB, ...
*/
// This allows to define names that conflicts RoboBoard global functions
class RGBConverter {
public:
    int toHex(uint8_t red, uint8_t green, uint8_t blue) {
        return red << 16 | green << 8 | blue;
    }
};
// We can create object with name "RGB"
RGBConverter RGB;
// Initialize program
void setup() {
  // Custom RGB can be accessed
  int color = RGB.toHex(0, 255, 0);
  // Totem RoboBoard functions can be accessed under "totem::" namespace
  totem::RGB.color(color);
}
// Loop program
void loop() {

}
// How does it work?
// If "Totem Prefix" option is disabled, line "using namespace totem" is added (inside Arduino.h)
// which removes requirement to explicitly type "totem::" everywhere.
