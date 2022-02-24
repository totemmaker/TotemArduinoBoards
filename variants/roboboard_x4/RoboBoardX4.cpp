/*
 Copyright (c) 2021 Totemmaker.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
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

extern "C" void __tone(uint8_t _pin, unsigned int frequency, unsigned long duration);
extern "C" void __noTone(uint8_t _pin);

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
    if ((_pin == GPIOA || _pin == GPIOB || _pin == GPIOC || _pin == GPIOD)
        && X4.getRevisionNum() != 10) {
        __tone(_pin, frequency, duration);
    }
    else {
        X4.dcAB.tone(frequency, duration);
    }
}
void noTone(uint8_t _pin) {
    if ((_pin == GPIOA || _pin == GPIOB || _pin == GPIOC || _pin == GPIOD)
        && X4.getRevisionNum() != 10) {
        __noTone(_pin);
    }
    else {
        X4.dcAB.tone(0, 0);
    }
}
