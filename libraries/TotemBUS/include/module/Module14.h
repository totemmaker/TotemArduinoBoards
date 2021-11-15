#ifndef MODULE14
#define MODULE14

#include "lib/TotemModuleX.h"

namespace Features14 {
struct Junction : public TotemModuleFeature {
    Junction(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Check if lines junction is detected
    bool isDetected() {
        return getCmd()->getInt();
    }
};
struct Color : public TotemModuleFeature {
    Color(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get color of detected line ['W','B',0]
    char get() {
        return getCmd()->getInt();
    }
    // Check if line is detected
    bool isDetected() {
        return get() != 0;
    }
    // Check if detected line color is white
    bool isWhite() {
        return get() == 'W';
    }
    // Check if detected line color is black
    bool isBlack() {
        return get() == 'B';
    }
};
struct Accuracy : public TotemModuleFeature {
    Accuracy(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get accuracy of line detection [0:100]%. Higher is better
    int get() {
        return getCmd()->getInt();
    }
    // Set minimum required accuracy to start line following [0:100]%
    void setThreshold(uint8_t contrast) {
        writeCmd(C("sensor/threshold"), contrast);
    }
};
struct Raw : public TotemModuleFeature {
    Raw(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get raw sensor contrast readings [0:100]%
    void get(uint8_t raw[8]) {
        uint8_t *ptr;
        if (!getCmd()->getData(ptr))
            return;
        for (int i=0; i<8; i++) 
            raw[i] = ptr[i];
    }
};
struct Pos : public TotemModuleFeature {
    Pos(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get line position [-35:35]
    int get() {
        return getCmd()->getInt();
    }
};
class Led : protected TotemModuleFeature {
    uint8_t ledState = 0b00000000;
public:
    Led(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
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
        ledState = state ? 0b11111111 : 0b00000000;
        writeCmd(ledState); 
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn() {
        return ledState;
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
        if (num >= 8) return;
        if (state) ledState |= (1 << (7-num));
        else ledState &= ~(1 << (7-num));
        writeCmd(ledState); 
    }
    // Read specified LED state [HIGH:LOW] (on / off)
    bool isOnX(uint8_t num) {
        if (num >= 8) return false;
        return ledState & (1 << (7-num));
    }
    // Set LED state by binary representation [B00000000:B11111111]
    void setBinary(uint8_t bin) {
        ledState = bin;
        writeCmd(ledState);
    }
    // Reset LED to default operation (display line position)
    void reset() {
        ledState = 0b00000000;
        writeCmd(-1);
    }
};
}

class Module14 : public TotemModuleX {
public:
    Features14::Junction junction;
    Features14::Color color;
    Features14::Pos pos;
    Features14::Accuracy accuracy;
    Features14::Raw raw;
    Features14::Led led;

    Module14(uint16_t serial = 0) : TotemModuleX(14, serial),
    junction(this, C("line/junction")),
    color(this, C("line/color")),
    pos(this, C("line/pos")),
    accuracy(this, C("sensor/range")),
    raw(this, C("sensor/raw")),
    led(this, C("led"))
    { }
};

#endif /* MODULE14 */
