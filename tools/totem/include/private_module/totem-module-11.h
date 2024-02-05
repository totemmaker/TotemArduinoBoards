/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE_11
#define INCLUDE_TOTEM_MODULE_11

#ifdef ARDUINO_ROBOBOARD_X4

#include "private_module/totem-x4-module.h"

namespace Features11 {
namespace cmd {
enum Commands {
    distance      = 0x2eb31462, //_Totem::CMD("distance"),
    rgbAll_totem  = 0x07969199, //_Totem::CMD("rgbAll/totem"),
    rgbAll_bright = 0xa0009f24, //_Totem::CMD("rgbAll/bright"),
    rgbAll        = 0xb6ca12a7, //_Totem::CMD("rgbAll"),
    rgbX          = 0xde063dac, //_Totem::CMD("rgbX"),
};
} // namespace cmd
template <int RGB_CNT>
class RGB {
    _Totem::TotemModule &m;
    struct {
        uint32_t color;
        bool isOn;
    } RGB_state[RGB_CNT] = {
        {0x18c712, true},
        {0xffff00, true},
        {0x1254c7, true},
        {0x18c712, true},
        {0xffff00, true},
        {0x1254c7, true},
        {0x18c712, true},
        {0xffff00, true}
    };
    bool RGB_isMixed = true;
    uint8_t ch = 0xFF;
public:
    RGB(_Totem::TotemModule &m) : m(m) { }
    // Turn LED on
    void on() {
        set(1);
    }
    // Turn LED off
    void off() {
        set(0);
    }
    // Toggle LED on / off
    void toggle() {
        if (ch == 0xFF && RGB_isMixed)
            for (int i=0; i<RGB_CNT; i++) {
                ch = i;
                set(!(RGB_state[i].isOn));
            }
        else
            set(!(isOn()));
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t state) {
        if (ch == 0xFF) {
            if (RGB_isMixed && state)
                for (int i=0; i<RGB_CNT; i++) {
                    ch = i;
                    color(RGB_state[i].color);
                }
            else
                color(state ? RGB_state[0].color : 0);
        }
        else if (ch < RGB_CNT)
            color(state ? RGB_state[ch].color : 0);
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn() {
        if (ch == 0xFF)
            for (int i=0; i<RGB_CNT; i++) { if (RGB_state[i].isOn) return true; }
        else if (ch < RGB_CNT)
            return RGB_state[ch].isOn;
        return false;
    }
    // Write LED with HEX color code [0:0xFFFFFF]
    void color(uint32_t hex) {
        if (ch == 0xFF) {
            m.write(cmd::rgbAll, hex);
            for (int i=0; i<RGB_CNT; i++) {
                if (hex) RGB_state[i].color = hex;
                RGB_state[i].isOn = hex != 0;
            }
            if (hex) RGB_isMixed = false;
        }
        else {
            m.write(cmd::rgbX, (uint32_t)ch << 24 | hex);
            if (hex) RGB_state[ch].color = hex;
            RGB_state[ch].isOn = hex != 0;
            RGB_isMixed = true;
        }
        ch = 0xFF;
    }
    // Set color by parameter color(R, G, B)
    void color(uint8_t r, uint8_t g, uint8_t b) { color((uint32_t)r << 16 | (uint32_t)g << 8 | b); }
    // Set all LED with Totem colors
    void colorTotem() {
        m.write(cmd::rgbAll_totem);
        RGB_state[0].color = 0x18c712;
        RGB_state[1].color = 0xffff00;
        RGB_state[2].color = 0x1254c7;
        RGB_state[3].color = 0x18c712;
        RGB_state[4].color = 0xffff00;
        RGB_state[5].color = 0x1254c7;
        RGB_state[6].color = 0x18c712;
        RGB_state[7].color = 0xffff00;
        for (int i=0; i<RGB_CNT; i++) { RGB_state[i].isOn = true; }
    }
    // Set LED state by binary representation [B00000000:B11111111]
    void setBinary(uint8_t mask) {
        for (int i=0; i<RGB_CNT; i++) {
            ch = i;
            set(mask & 1);
            mask >>= 1;
        }
    }
    // Enable bright mode
    void setBrightMode(bool on) {
        m.write(cmd::rgbAll_bright, on);
    }
    // Index trough specific LED [0:7]
    RGB& operator[](uint8_t num) {
        if (num < RGB_CNT) ch = num;
        return *this;
    }
};
} // namespace Features11

class TotemModule11 : public TotemX4Module {
public:
    // Available TotemModule11 events registered with addEvent() function
    enum {
        evtDistance = 11 << 16,
    };
    using cmd = Features11::cmd::Commands;
    // RGB LED control
    Features11::RGB<8> rgb;

    // Get distance in millimeters
    uint32_t getMM() {
        uint32_t mm = readCmdInt(cmd::distance);
        if (mm >= 2000) mm = 0;
        return mm;
    }
    // Get distance in centimeters
    uint32_t getCm() { return getMM() / 10; }
    // Get distance in foots
    float getFoot() { return (float)getMM() * 0.00328084; }
    // Get distance in inches
    float getInch() { return (float)getMM() * 0.0393701; }
    // Check if sensor is detecting any obstacle
    bool isDetected() { return getMM() != 0; }

    TotemModule11(uint16_t serial = 0) : TotemX4Module(11, serial, eventsList),
    rgb(module)
    { }
private:
    _Totem::Event eventsList[1] = {
        cmd::distance,
    };
};

#else /* ARDUINO_ROBOBOARD_X4 */
#error "TotemModule11 is only supported with RoboBoard X4"
#endif

#endif /* INCLUDE_TOTEM_MODULE_14 */
