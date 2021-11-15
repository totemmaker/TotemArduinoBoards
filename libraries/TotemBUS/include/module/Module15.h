#ifndef MODULE15
#define MODULE15

#include "lib/TotemModuleX.h"

namespace Features15 {
class Knob : public TotemModuleFeature {
public:
    Knob(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) {}
    // Get knob position [0:255]
    int get() {
        return getCmd()->getInt();
    }
};
class Button : public TotemModuleFeature {
public:
    Button(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) {}
    // Is button pressed
    bool isPressed() {
        return getCmd()->getInt();
    }
    // Is button released
    bool isReleased() {
        return !isPressed();
    }
};
class Led : protected TotemModuleFeature {
    struct {
        uint32_t cmd;
        uint8_t alpha;
    } led[3];
    uint8_t ledState = 0;
public:
    Led(TotemModuleX *m, uint32_t c0, uint32_t cA, uint32_t cB, uint32_t cC) : 
    TotemModuleFeature(m, c0) {
        led[0].cmd = cA; led[0].alpha = 255;
        led[1].cmd = cB; led[1].alpha = 255;
        led[2].cmd = cC; led[2].alpha = 255;
    }
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
        set(isOn() ? 0 : 1);
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t state) {
        ledState = state ? 0b111 : 0b000;
        writeCmd(state ? led[0].alpha : 0); 
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn() {
        return ledState;
    }
    // Set LED brightness [0:255]
    void setAlpha(uint8_t alpha) {
        led[0].alpha = led[1].alpha = led[2].alpha = alpha;
        set(1);
    }
    // Turn on specified LED (A, B, C)
    void onX(uint8_t num) {
        setX(num, 1);
    }
    // Turn off specified LED (A, B, C)
    void offX(uint8_t num) {
        setX(num, 0);
    }
    // Toggle LED specified LED (on / off)
    void toggleX(uint8_t num) {
        setX(num, isOnX(num) ? 0 : 1);
    }
    // Set specified LED state [HIGH:LOW] (on / off)
    void setX(uint8_t num, uint8_t state) {
        if (num >= 3) return;
        if (state) ledState |= (1 << (2-num));
        else ledState &= ~(1 << (2-num));
        writeCmd(led[num].cmd, state ? led[num].alpha : 0);
    }
    // Read specified LED state [HIGH:LOW] (on / off)
    bool isOnX(uint8_t num) {
        if (num >= 3) return false;
        return ledState & (1 << (2-num));
    }
    // Set LED brightness [0:255]
    void setAlphaX(uint8_t num, uint8_t alpha) {
        if (num >= 3) return;
        led[num].alpha = alpha;
        setX(num, 1);
    }
    // Set LED state by binary representation [B000:B111]
    void setBinary(uint8_t bin) {
        ledState = bin & 0b111;
        if (ledState == 0b111) writeCmd(led[0].alpha);
        else if (ledState == 0b000) writeCmd(0);
        else {
            writeCmd(led[0].cmd, (bin & 0b100) ? led[0].alpha : 0);
            writeCmd(led[1].cmd, (bin & 0b010) ? led[1].alpha : 0);
            writeCmd(led[2].cmd, (bin & 0b001) ? led[2].alpha : 0);
        }
    }
    // Reset LED to default operation (display line position)
    void reset() {
        ledState = 0b000;
        getModule().write(C("ledAll/reset"));
    }
};
}

class Module15 : public TotemModuleX {
public:
    Features15::Knob knobA, knobB, knobC;
    Features15::Button buttonA, buttonB, buttonC;
    Features15::Led led;//, ledA, ledB, ledC;
    
    void setKnobBits(uint8_t resolution) {
        module.write(C("knobAll/bits"), resolution);
    }
    
    Module15(uint16_t serial = 0) : TotemModuleX(15, serial),
    knobA(this, C("knobA")), knobB(this, C("knobB")), knobC(this, C("knobC")),
    buttonA(this, C("buttonA")), buttonB(this, C("buttonB")), buttonC(this, C("buttonC")),
    led(this, C("ledAll"), C("ledA"), C("ledB"), C("ledC"))
    { }
};

#endif /* MODULE15 */
