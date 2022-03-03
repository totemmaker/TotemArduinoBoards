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
#ifndef MODULE15
#define MODULE15

#include "lib/TotemEventModule.h"

namespace Features15 {
using namespace Feature;
namespace cmd {
enum Commands {
    knobA        = CMD("knobA"),
    knobB        = CMD("knobB"),
    knobC        = CMD("knobC"),
    knobAll_bits = CMD("knobAll/bits"),
    ledAll_reset = CMD("ledAll/reset"),
    ledAll       = CMD("ledAll"),
    ledA         = CMD("ledA"),
    ledB         = CMD("ledB"),
    ledC         = CMD("ledC"),
    buttonA      = CMD("buttonA"),
    buttonB      = CMD("buttonB"),
    buttonC      = CMD("buttonC"),
};
} // namespace cmd
class Knob : public ChannelEvent {
    const uint32_t channels[3] = {cmd::knobA, cmd::knobB, cmd::knobC};
public:
    Knob(TotemModuleData &d) : ChannelEvent(d, channels) { }
    // Get knob position [0:255]
    int getPosition(uint8_t ch) {
        return this->getChannel(ch).getInt();
    }
};
class Button : public ChannelEvent {
    const uint32_t channels[3] = {cmd::buttonA, cmd::buttonB, cmd::buttonC};
public:
    Button(TotemModuleData &d) : ChannelEvent(d, channels) { }
    // Is button pressed
    bool isPressed(uint8_t ch) {
        return this->getChannel(ch).getInt();
    }
    // Is button released
    bool isReleased(uint8_t ch) {
        return !isPressed(ch);
    }
};
template <int LED_CNT>
class Led : public NoEvent {
    const uint32_t channels[3] = {cmd::ledA, cmd::ledB, cmd::ledC};
    uint8_t led_alpha[LED_CNT] = { 255, 255, 255 };
    uint8_t ledState = 0;
public:
    Led(TotemModuleData &d) : NoEvent(d, channels) { }
    // Turn LED on
    void on(uint8_t ch) {
        this->set(ch, 1);
    }
    // Turn  LED off
    void off(uint8_t ch) {
        this->set(ch, 0);
    }
    // Toggle LED (on / off)
    void toggle(uint8_t ch) {
        if (ch == chAll)
            this->setBinary(~ledState);
        else
            this->set(ch, !(this->isOn(ch)));
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t ch, uint8_t state) {
        if (ch == chAll) {
            ledState = state ? 0xFF : 0;
            for (int i=0; i<LED_CNT; i++) { this->writeChannel(i, state ? led_alpha[i] : 0); }
        }
        else if (ch < LED_CNT) {
            if (state) ledState |= (1 << ch);
            else ledState &= ~(1 << ch);
            this->writeChannel(ch, state ? led_alpha[ch] : 0);
        }
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn(uint8_t ch) {
        if (ch >= LED_CNT) return false;
        return ledState & (1 << ch);
    }
    // Set LED brightness [0:255]
    void setAlpha(uint8_t ch, uint8_t alpha) {
        if (ch == chAll)
            for (int i=0; i<LED_CNT; i++) { led_alpha[i] = alpha; }
        else if (ch < LED_CNT)
            led_alpha[ch] = alpha;
        else
            return;
        set(ch, 1);
    }
    
    // Reset LED to default operation (display line position)
    void reset() {
        ledState = 0;
        this->writeCmd(cmd::ledAll_reset);
    }
    // Set LED state by binary representation [B000:B111]
    void setBinary(uint8_t bin) {
        ledState = bin & 0b111;
        for (int i=0; i<LED_CNT; i++) {
            this->writeChannel(i, (bin & 1) ? led_alpha[i] : 0);
            bin >>= 1;
        }
    }
};
} // namespace Features15

class Module15 : public Feature::TotemEventModule {
    Feature::Event eventsList[6] = {
        cmd::knobA,
        cmd::knobB,
        cmd::knobC,
        cmd::buttonA,
        cmd::buttonB,
        cmd::buttonC,
    };
public:
    using cmd = Features15::cmd::Commands;
    Features15::Knob knob;
    Features15::Button button;
    Features15::Led<3> led;
    
    // Configure knob resolution in bits [6,8,10,12]
    void setKnobBits(uint8_t resolution) {
        data.module.write(cmd::knobAll_bits, resolution);
    }

    Module15(uint16_t serial = 0) : Feature::TotemEventModule(15, serial, eventsList),
    knob(data), button(data), led(data)
    { }
};

#endif /* MODULE15 */
