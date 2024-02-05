/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE_14
#define INCLUDE_TOTEM_MODULE_14

#ifdef ARDUINO_ROBOBOARD_X4

#include "private_module/totem-x4-module.h"

namespace Features14 {
namespace cmd {
enum Commands {
    sensor_threshold = 0x96534e9f, //CMD("sensor/threshold"),
    sensor_range     = 0xe04bc4e1, //CMD("sensor/range"),
    sensor_raw       = 0x13d43132, //CMD("sensor/raw"),
    line_junction    = 0x4c055d1c, //CMD("line/junction"),
    line_color       = 0xa8d5682f, //CMD("line/color"),
    line_pos         = 0x9cbc99f2, //CMD("line/pos"),
    led              = 0x406aeaca, //CMD("led"),
};
} // namespace cmd
template <int LED_CNT>
class Led {
    _Totem::TotemModule &m;
    uint8_t ledState = 0;
    uint8_t ch = 0xFF;
public:
    Led(_Totem::TotemModule &m) : m(m) { }
    // Turn LED on
    void on() {
        set(1);
    }
    // Turn LED off
    void off() {
        set(0);
    }
    // Toggle LED (on / off)
    void toggle() {
        if (ch == 0xFF)
            setBinary(~ledState);
        else
            set(!(isOn()));
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t state) {
        if (ch == 0xFF)
            ledState = state ? 0xFF : 0;
        else if (ch < LED_CNT) {
            if (state) ledState |= (1 << ch);
            else ledState &= ~(1 << ch);
        }
        else
            return;
        m.write(cmd::led, ledState);
        ch = 0xFF;
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn() {
        if (ch >= LED_CNT) return false;
        bool state = ledState & (1 << ch);
        ch = 0xFF;
        return state;
    }

    // Set all LED state by binary representation [B00000000:B11111111]
    void setBinary(uint8_t bin) {
        uint8_t reverse = 0;
        ledState = bin;
        for (int i=0; i<8; i++) {
            reverse <<= 1;
            reverse |= (bin & 1);
            bin >>= 1;
        }
        m.write(cmd::led, reverse);
        ch = 0xFF;
    }
    // Reset all LED to default operation (display line position)
    void reset() {
        ledState = 0;
        m.write(cmd::led, -1);
        ch = 0xFF;
    }
    // Index trough specific LED [0:7]
    Led& operator[](uint8_t num) {
        if (num < LED_CNT) ch = num;
        return *this;
    }
};
} // namespace Features14
class TotemModule14 : public TotemX4Module {
public:
    // Available TotemModule14 events registered with addEvent() function
    enum {
        evtRaw = 14 << 16,
        evtPos,
        evtColor,
    };
    using cmd = Features14::cmd::Commands;
    // LED control
    Features14::Led<8> led;

    // Get line position [-35:35]
    int getPos() { return readCmdInt(cmd::line_pos); }
    // Get color of detected line ['W','B',0]
    char getColor() { return readCmdInt(cmd::line_color); }
    // Get raw sensor contrast readings [0:100]%
    void getRaw(uint8_t raw[8]) {
        uint8_t *ptr;
        if (!(readCmd(cmd::sensor_raw).getData(ptr)))
            return;
        for (int i=0; i<8; i++)
            raw[i] = ptr[i];
    }

    // Check if detected line color is white
    bool isWhite() { return getColor() == 'W'; }
    // Check if detected line color is black
    bool isBlack() { return getColor() == 'B'; }

    // Check if line is currently detected
    bool isDetected() { return getColor() != 0; }
    // Check if lines junction is detected (got from color)
    bool isJunction() { return getColor() == 0; }

    // Get accuracy of line detection [0:100]%. Higher is better
    int getAccuracy() { return readCmdInt(cmd::sensor_range); }
    // Set minimum required accuracy to start line following [0:100]%
    void setThreshold(uint8_t contrast) {
        writeCmdInt(cmd::sensor_threshold, contrast);
    }
    // Get color of detected line ['W','B',0]
    void setColor(char color) {
        writeCmdInt(cmd::line_color, color);
    }

    TotemModule14(uint16_t serial = 0) : TotemX4Module(14, serial, eventsList),
    led(module)
    { }
private:
    uint8_t rawBuffer[8];
    _Totem::Event eventsList[3] = {
        {cmd::sensor_raw, rawBuffer, 8},
        cmd::line_pos,
        cmd::line_color,
    };
};

#else /* ARDUINO_ROBOBOARD_X4 */
#error "TotemModule14 is only supported with RoboBoard X4"
#endif

#endif /* INCLUDE_TOTEM_MODULE_14 */
