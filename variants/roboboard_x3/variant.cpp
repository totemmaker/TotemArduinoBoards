#include <Arduino.h>
#include "private/totem-version.h"

void RoboBoard_begin(void (*)(), uint32_t, uint32_t);
void initRoboBoard() __attribute__((weak));
void initRoboBoard() {
#ifdef _MENU_CHARGING_ON
    Board.setChargingMode(true);
#endif
#ifdef _MENU_STATUS_ON
    Board.setStatusSound(true);
    Board.setStatusRGB(true);
#endif
}

void initVariant(void) {
    RoboBoard_begin(initRoboBoard, ESP_ARDUINO_VERSION, TOTEM_ARDUINO_BUILD);
#ifdef _MENU_REMOTE_APP
    TotemApp.begin();
#endif
}
