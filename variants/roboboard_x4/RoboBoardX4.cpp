#include <Arduino.h>

bool RoboBoardX4_initialize();

void initVariant(void) {
#ifdef ARDUINO_ROBOBOARD_X4
    RoboBoardX4_initialize();
#endif
#ifdef ROBOBOARD_X4_APP_CONTROL_ENABLED
    X4.enableAppControl();
#endif
}