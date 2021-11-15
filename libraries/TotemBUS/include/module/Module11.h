#ifndef MODULE11
#define MODULE11

#include "lib/TotemModuleX.h"

namespace Features11 {
class Distance : public TotemModuleFeature {
public:
    Distance(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) {}
    // Get distance in milimeters
    uint32_t getMM() {
        uint32_t mm = getCmd()->getInt();
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
    bool inRange() {
        return getMM() != 0;
    }
};
class RGB : protected TotemModuleFeature {
    uint32_t lastColor = 0x00FF00;
    bool stateOn = true;
public:
    RGB(TotemModuleX *m) : TotemModuleFeature(m) {}
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
        color(state ? lastColor : 0);
    }
    // Read LED state [HIGH:LOW] (on / off)
    int isOn() {
        return stateOn;
    }
    // Set LED with red, green, blue [0:255]
    void color(uint8_t r, uint8_t g, uint8_t b) {
        color(r << 16 | g << 8 | b);
    }
    // Set LED with HEX color code [0:0xFFFFFFFF] (including brightness)
    void color(uint32_t hex) {
        writeCmd(C("rgbAll"), hex);
        stateOn = hex != 0;
        if (stateOn) lastColor = hex;
    }
    // Write individual [0:7] LED with red, green, blue [0:255]
    void colorX(uint8_t num, uint8_t r, uint8_t g, uint8_t b) {
        colorX(num, r << 16 | g << 8 | b);
    }
    // Write individual [0:7] LED with HEX color code [0:0xFFFFFF]
    void colorX(uint8_t num, uint32_t hex) {
        writeCmd(C("rgbX"), num << 24 | hex);
        stateOn = hex != 0;
        if (stateOn) lastColor = hex;
    }
    // Set all LED with Totem colors
    void colorTotem() {
        writeCmd(C("rgbAll/totem"));
        lastColor = 0x00FF00;
        stateOn = true;
    }
    // Enable bright mode
    void setBrightMode(bool on) {
        writeCmd(C("rgbAll/bright"), on);
    }
};
}

class Module11 : public TotemModuleX {
public:
    Features11::Distance distance;
    Features11::RGB rgb;

    Module11(uint16_t serial = 0) : TotemModuleX(11, serial),
    distance(this, C("distance")), rgb(this)
    { }
};

#endif /* MODULE11 */
