/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE_15
#define INCLUDE_TOTEM_MODULE_15

#ifdef ARDUINO_ROBOBOARD_X4

#include "private_module/totem-x4-module.h"

namespace Features15 {
namespace cmd {
enum Commands {
    knobA        = 0x8068c520, //CMD("knobA"),
    knobB        = 0x8368c9d9, //CMD("knobB"),
    knobC        = 0x8268c846, //CMD("knobC"),
    knobAll_bits = 0x2ef5b8c9, //CMD("knobAll/bits"),
    ledAll_reset = 0x04595f5d, //CMD("ledAll/reset"),
    ledAll       = 0x7002f4f1, //CMD("ledAll"),
    ledA         = 0xf34f38d1, //CMD("ledA"),
    ledB         = 0xf04f3418, //CMD("ledB"),
    ledC         = 0xf14f35ab, //CMD("ledC"),
    buttonA      = 0xc1ece790, //CMD("buttonA"),
    buttonB      = 0xc4ecec49, //CMD("buttonB"),
    buttonC      = 0xc3eceab6, //CMD("buttonC"),
};
} // namespace cmd
template <int LED_CNT>
class Led {
    _Totem::TotemModule &m;
    const uint32_t channels[3] = {cmd::ledA, cmd::ledB, cmd::ledC};
    uint8_t led_alpha[LED_CNT] = { 255, 255, 255 };
    uint8_t ledState = 0;
    uint8_t ch = 0xFF;
public:
    Led(_Totem::TotemModule &m) : m(m) { }
    // Turn LED on
    void on() {
        set(1);
    }
    // Turn  LED off
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
        if (ch == 0xFF) {
            ledState = state ? 0xFF : 0;
            for (int i=0; i<LED_CNT; i++) { m.write(channels[i], state ? led_alpha[i] : 0); }
        }
        else if (ch < LED_CNT) {
            if (state) ledState |= (1 << ch);
            else ledState &= ~(1 << ch);
            m.write(channels[ch], state ? led_alpha[ch] : 0);
        }
        ch = 0xFF;
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn() {
        if (ch >= LED_CNT) return false;
        return ledState & (1 << ch);
    }
    // Set LED brightness [0:255]
    void setAlpha(uint8_t alpha) {
        if (ch == 0xFF)
            for (int i=0; i<LED_CNT; i++) { led_alpha[i] = alpha; }
        else if (ch < LED_CNT)
            led_alpha[ch] = alpha;
        else
            return;
        set(1);
    }

    // Set all LED state by binary representation [B000:B111]
    void setBinary(uint8_t bin) {
        ledState = bin & 0b111;
        for (int i=0; i<LED_CNT; i++) {
            m.write(channels[i], (bin & 1) ? led_alpha[i] : 0);
            bin >>= 1;
        }
        ch = 0xFF;
    }
    // Reset all LED to default operation (display knob position)
    void reset() {
        ledState = 0;
        m.write(cmd::ledAll_reset);
        ch = 0xFF;
    }
    // Index trough specific LED [0:72]
    Led& operator[](uint8_t num) {
        if (num < LED_CNT) ch = num;
        return *this;
    }
};
} // namespace Features15

class TotemModule15 : public TotemX4Module {
public:
    // Available TotemModule15 events registered with addEvent() function
    enum {
        evtKnobA = 15 << 16,
        evtKnobB,
        evtKnobC,
        evtButtonA,
        evtButtonB,
        evtButtonC,
    };
    using cmd = Features15::cmd::Commands;
    // LED control
    Features15::Led<3> led;

    // Get knob A position [0:255]
    int getKnobA() { return readCmdInt(cmd::knobA); }
    // Get knob B position [0:255]
    int getKnobB() { return readCmdInt(cmd::knobB); }
    // Get knob C position [0:255]
    int getKnobC() { return readCmdInt(cmd::knobC); }

    // Get button A state [0:1]
    int getButtonA() { return readCmdInt(cmd::buttonA); }
    // Get button B state [0:1]
    int getButtonB() { return readCmdInt(cmd::buttonB); }
    // Get button C state [0:1]
    int getButtonC() { return readCmdInt(cmd::buttonC); }
    
    // Configure knob resolution in bits [6,8,10,12]
    void setKnobBits(uint8_t resolution) {
        writeCmdInt(cmd::knobAll_bits, resolution);
    }

    TotemModule15(uint16_t serial = 0) : TotemX4Module(15, serial, eventsList),
    led(module)
    { }
private:
    _Totem::Event eventsList[6] = {
        cmd::knobA,
        cmd::knobB,
        cmd::knobC,
        cmd::buttonA,
        cmd::buttonB,
        cmd::buttonC,
    };
};

#else /* ARDUINO_ROBOBOARD_X4 */
#error "TotemModule15 is only supported with RoboBoard X4"
#endif

#endif /* INCLUDE_TOTEM_MODULE_15 */
