/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_TOTEMAPP
#define INCLUDE_TOTEM_TOTEMAPP

#include <stdint.h>

namespace _Totem {

class TotemAppClass {
public:
    /// @brief Make RoboBoard discoverable in Totem App
    /// @param name (optional) board name
    int begin(const char *name = nullptr);
    /// @brief Brake existing connection with Totem App
    void disconnect();
    /// @brief Wait until Totem App is connected
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - connected. false - timeout
    bool wait(uint32_t timeout = 0);

    /// @brief Events returned in App event function
    enum {
        evtFunctionA,
        evtFunctionB,
        evtFunctionC,
        evtFunctionD,
        evtConnect,
        evtDisconnect,
    };
    
    /// @brief Register function to receive App events
    /// @param func function
    void addEvent(void (*func)(int evt, int value));

    /// @brief Motor commands sent by Totem App
    enum {
        cmdPosA = 0x4b9d4499,
        cmdPosB = 0x489d3fe0,
        cmdPosC = 0x499d4173,
        cmdPowerA = 0xaba01c49,
        cmdPowerB = 0xa8a01790,
        cmdPowerC = 0xa9a01923,
        cmdPowerD = 0xaea02102,
        cmdFunctionA = 0x1349f298,
        cmdFunctionB = 0x1649f751,
        cmdFunctionC = 0x1549f5be,
        cmdFunctionD = 0x1849fa77,
    };

    /// @brief Register command override function
    /// @param func function
    void addOverride(bool (*func)(int cmd, int value));
};

} // namespace _Totem

extern _Totem::TotemAppClass TotemApp;

#endif /* INCLUDE_TOTEM_TOTEMAPP */
