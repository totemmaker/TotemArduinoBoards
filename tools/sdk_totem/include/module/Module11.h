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
#ifndef MODULE11
#define MODULE11

#include "lib/TotemEventModule.h"

namespace Features11 {
using namespace Feature;
namespace cmd {
enum Commands {
    distance      = CMD("distance"),
    rgbAll_totem  = CMD("rgbAll/totem"),
    rgbAll_bright = CMD("rgbAll/bright"),
    rgbAll        = CMD("rgbAll"),
    rgbX          = CMD("rgbX"),
};
} // namespace cmd
class Distance : public SingleEvent {
    const uint32_t events[1] = {cmd::distance};
public:
    Distance(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get distance in milimeters
    uint32_t getMM() {
        uint32_t mm = this->getCmd(cmd::distance).getInt();
        if (mm >= 2000) mm = 0;
        return mm;
    }
    // Get dinstance in centimeters
    uint32_t getCm() {
        return getMM() / 10;
    }
    // Get distance in foots
    float getFoot() {
        return (float)getMM() * 0.00328084f;
    }
    // Get distance in inches
    float getInch() {
        return (float)getMM() * 0.0393701f;
    }
    // Check if sensor is detecting any obstacle
    bool isDetected() {
        return getMM() != 0;
    }
};
template <int RGB_CNT>
class RGB : public NoEvent {
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
public:
    RGB(TotemModuleData &d) : NoEvent(d) { }
    // Turn LED on
    void on(uint8_t ch) {
        this->set(ch, 1);
    }
    // Turn LED off
    void off(uint8_t ch) {
        this->set(ch, 0);
    }
    // Toggle LED on / off
    void toggle(uint8_t ch) {
        if (ch == chAll && RGB_isMixed)
            for (int i=0; i<RGB_CNT; i++) { this->set(i, !(RGB_state[i].isOn)); }
        else
            this->set(ch, !(this->isOn(ch)));
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t ch, uint8_t state) {
        if (ch == chAll) {
            if (RGB_isMixed && state)
                for (int i=0; i<RGB_CNT; i++) {
                    this->colorHEX(i, RGB_state[i].color);
                }
            else
                this->colorHEX(ch, state ? RGB_state[0].color : 0);
        }
        else if (ch < RGB_CNT)
            this->colorHEX(ch, state ? RGB_state[ch].color : 0);
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn(uint8_t ch) {
        if (ch == chAll)
            for (int i=0; i<RGB_CNT; i++) { if (RGB_state[i].isOn) return true; }
        else if (ch < RGB_CNT)
            return RGB_state[ch].isOn;
        return false;
    }
    // Write [0:7] LED with brightness, red, green, blue [0:255]
    void colorARGB(uint8_t ch, uint8_t alpha, uint8_t r, uint8_t g, uint8_t b) {
        if (alpha != 255) {
            r = (uint32_t)r * (uint32_t)alpha / 255;
            g = (uint32_t)g * (uint32_t)alpha / 255;
            b = (uint32_t)b * (uint32_t)alpha / 255;
        }
        uint32_t hex = (uint32_t)r << 16 | (uint32_t)g << 8 | b;
        if (ch == chAll) {
            this->writeCmd(cmd::rgbAll, hex);
            for (int i=0; i<RGB_CNT; i++) {
                if (hex) RGB_state[i].color = hex;
                RGB_state[i].isOn = hex != 0;
            }
            if (hex) RGB_isMixed = false;
        }
        else {
            this->writeCmd(cmd::rgbX, (uint32_t)ch << 24 | hex);
            if (hex) RGB_state[ch].color = hex;
            RGB_state[ch].isOn = hex != 0;
            RGB_isMixed = true;
        }
    }
    // Write [0:7] LED with red, green, blue [0:255]
    void colorRGB(uint8_t ch, uint8_t r, uint8_t g, uint8_t b) {
        this->colorARGB(ch, 255, r, g, b);
    }
    // Write [0:7] LED with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void colorAHEX(uint8_t ch, uint8_t alpha, uint32_t hex) {
        this->colorARGB(ch, alpha, hex >> 16, hex >> 8, hex);
    }
    // Write [0:7] LED with HEX color code [0:0xFFFFFF]
    void colorHEX(uint8_t ch, uint32_t hex) {
        this->colorARGB(ch, 255, hex >> 16, hex >> 8, hex);
    }
    // Enable bright mode
    void setBrightMode(bool on) {
        this->writeCmd(cmd::rgbAll_bright, on);
    }

    // Set all LED with Totem colors
    void colorTotem() {
        this->writeCmd(cmd::rgbAll_totem);
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
            this->set(i, mask & 1);
            mask >>= 1;
        }
    }
};
} // namespace Features11

class Module11 : public Feature::TotemEventModule {
    Feature::Event eventsList[1] = {
        cmd::distance,
    };
public:
    using cmd = Features11::cmd::Commands;
    Features11::Distance distance;
    Features11::RGB<8> rgb;

    Module11(uint16_t serial = 0) : Feature::TotemEventModule(11, serial, eventsList),
    distance(data), rgb(data)
    { }
};

#endif /* MODULE11 */
