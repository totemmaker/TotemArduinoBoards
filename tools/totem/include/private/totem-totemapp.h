/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_TOTEMAPP
#define INCLUDE_TOTEM_TOTEMAPP

#include <WString.h>

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

    /// @brief Register TotemApp value override function
    /// @param func callback bool onOverride(int cmd, int value)
    void addOverride(bool (*onOverrideValue)(int cmd, int value));
    /// @brief Register TotemApp string override function
    /// @param func callback bool onOverride(int cmd, String string)
    void addOverride(bool (*onOverrideString)(int cmd, String string));

    [[deprecated("Use TotemApp.addOnString(onString)")]]
    void addOverride(bool (*func)(int cmd, const char *data, int len));

    /// @brief Register value write for remote "sendValue" in TotemArduino library
    /// @param func callback void onValue(int id, int value)
    void addOnSend(void (*onValue)(int id, int value));
    /// @brief Register data write for remote "sendString" in TotemArduino library
    /// @param func callback void onString(int id, String str)
    void addOnSend(void (*onString)(int id, String str));
    /// @brief Register value read for remote "readValue" in TotemArduino library
    /// @param func callback int onReadValue(int id)
    void addOnRead(int (*onReadValue)(int id));
    /// @brief Register string read for remote "readString" in TotemArduino library
    /// @param func callback String onReadString(int id)
    void addOnRead(String (*onReadString)(int id));

    /// @brief Send 32-bit value to TotemArduino library
    /// @param id identifier
    /// @param value 32-bit value
    /// @return [true]-success, [false]-error
    bool sendValue(int id, int value);
    /// @brief Send data array to TotemArduino library
    /// @param id identifier
    /// @param data string or data array
    /// @param len data length. [-1] - acquire from "data"
    /// @return [true]-success, [false]-error
    bool sendString(int id, const void *data, int len = -1);
    /// @brief Send string (text) to TotemArduino library
    /// @param id identifier
    /// @param string String object
    /// @return [true]-success, [false]-error
    bool sendString(int id, String string) { return sendString(id, string.c_str(), string.length()); }

    [[deprecated("Use TotemApp.sendString(id, data, len)")]]
    int sendData(int command, const void *data, int len) { return sendString(command, (const char*)data, len); }
};

} // namespace _Totem

namespace totem {

extern _Totem::TotemAppClass TotemApp;

} // namespace totem

#endif /* INCLUDE_TOTEM_TOTEMAPP */
