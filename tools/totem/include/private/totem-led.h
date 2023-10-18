/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_LED
#define INCLUDE_TOTEM_LED

#include "pins_arduino.h"

class IOLED {
public:
    /// @brief Create LED control interface
    /// @param pin GPIO pin number
    /// @param onState LED pin state when ON [LOW:HIGH]
    IOLED(uint8_t pin, uint8_t onState = 1);
    /// @brief Turn ON
    void on();
    /// @brief Turn OFF
    void off();
    /// @brief Toggle between ON / OFF state
    void toggle();
    /// @brief Is turned ON
    /// @return [true:false] - is ON
    bool isOn();
    /// @brief Blink specified number of times
    /// @param count number of blinks (5)
    /// @param onTime on time (ms) (100)
    /// @param offTime off time (ms) (200)
    void blink(uint32_t count = 5, uint32_t onTime = 100, uint32_t offTime = 200);
    /// @brief Wait for function blink() to stop
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - blink stopped. false - timeout
    bool wait(uint32_t timeout = 0);
    /// @brief Set state
    /// @param state [true:false] - ON / OFF
    void setState(uint8_t state);
    /// @brief Get state
    /// @return [true:false] - ON / OFF
    int getState();
private:
    /// @brief Private value
    struct LedState {
        uint8_t state = 0;
        uint8_t initialized = 0;
    } _status;
    /// @brief Private value
    const uint8_t _ledPin;
    /// @brief Private value
    const uint8_t _ledOnState;
};

extern IOLED LED;

#endif /* INCLUDE_TOTEM_LED */
