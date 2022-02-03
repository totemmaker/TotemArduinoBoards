#ifndef MODULE15
#define MODULE15

#include "lib/TotemEventModule.h"

namespace Features15 {
template <int KNOB_CNT>
class Knob : public Feature::MultiEvent {
    const uint32_t cmdList[KNOB_CNT] = {
        Feature::CMD("knobA"), Feature::CMD("knobB"), Feature::CMD("knobC")
    };
public:
    Knob(TotemModuleData &d) : Feature::MultiEvent(d, cmdList) { }
    // Get knob position [0:255]
    int get(uint8_t ch) {
        return this->getCmd(ch)->getInt();
    }
};
template <int BUTTON_CNT>
class Button : public Feature::MultiEvent {
    const uint32_t cmdList[BUTTON_CNT] = {
        Feature::CMD("buttonA"), Feature::CMD("buttonB"), Feature::CMD("buttonC")
    };
public:
    Button(TotemModuleData &d) : Feature::MultiEvent(d, cmdList) { }
    // Is button pressed
    bool isPressed(uint8_t ch) {
        return this->getCmd(ch)->getInt();
    }
    // Is button released
    bool isReleased(uint8_t ch) {
        return !isPressed(ch);
    }
};
template <int LED_CNT>
class Led : public Feature::Simple {
    uint8_t led_alpha[LED_CNT] = { 255, 255, 255 };
    uint8_t ledState = 0;
    const uint32_t cmdList[LED_CNT] = {
        Feature::CMD("ledA"), Feature::CMD("ledB"), Feature::CMD("ledC")
    };
public:
    Led(TotemModuleData &d) : Feature::Simple(d, cmdList) { }
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
        this->writeCustomCmd(Feature::CMD("ledAll/reset"));
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
}

class Module15 : public TotemEventModule {
public:
    Features15::Knob<3> knob;
    Features15::Button<3> button;
    Features15::Led<3> led;
    
    void setKnobBits(uint8_t resolution) {
        data.module.write(Feature::CMD("knobAll/bits"), resolution);
    }
    
    Module15(uint16_t serial = 0) : TotemEventModule(15, serial),
    knob(data), button(data), led(data)
    { }
};

#endif /* MODULE15 */
