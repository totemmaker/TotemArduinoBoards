#ifndef MODULE22
#define MODULE22

#include "lib/TotemModuleX.h"

namespace Features22 {
struct Color : public TotemModuleFeature {
    Color(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get current color HEX value [0:0xFFFFFF]
    uint32_t getHex() {
        return getCmd()->getInt();
    }
    // Get current color Red amount [0:255]
    uint8_t getR() {
        return (getHex() >> 16) & 0xFF;
    }
    // Get current color Green amount [0:255]
    uint8_t getG() {
        return (getHex() >> 8) & 0xFF;
    }
    // Get current color Blue amount [0:255]
    uint8_t getB() {
        return (getHex()) & 0xFF;
    }
};
struct Get : public TotemModuleFeature {
    Get(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get value
    uint32_t get() {
        return getCmd()->getInt();
    }
};
struct Temp : public TotemModuleFeature {
    Temp(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get temperature in Celsius
    float getC() {
        float value = getCmd()->getInt();
        return value / 100;
    }
    // Get temperature in Farenheit
    float getF() {
        return getC() * 9 / 5 + 32;
    }
    // Get temperature in Kelvin
    float getK() {
        return getC() + 273.15f;
    }
};
struct TempNTC : public Temp {
    TempNTC(TotemModuleX *m, uint32_t cmd) : Temp(m, cmd) { }
    // Get NTC sensor resitance
    uint32_t getResistance() {
        return getCmd()->getInt();
    }
};
struct Pressure : public TotemModuleFeature {
    Pressure(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get pressure in Pa (Pascal)
    float getPa() {
        return getCmd()->getInt();
    }
    // Get pressure in hPa (hectopascal)
    float gethPa() {
        return getPa() / 100;
    }
    // Get pressure in mbar (milibar)
    float getMbar() {
        return getPa() / 100;
    }
    // Get pressure in Bar (Bar)
    float getBar() {
        return getPa() / 100000;
    }
    // Get pressure in PSI (Pounds per square inch)
    float getPsi() {
        return getPa() / 6895;
    }
};
struct Altitude : public TotemModuleFeature {
    Altitude(TotemModuleX *m, uint32_t cmd) : TotemModuleFeature(m, cmd) { }
    // Get altitude in M (Meter)
    float getMeter() {
        return getFoot() * 0.3048f;
    }
    // Get altitude in Ft (Foot)
    float getFoot() {
        return getCmd()->getInt();
    }
    // Get altitude in in (Inch)
    float getInch() {
        return getFoot() * 12;
    }
};
class Led : protected TotemModuleFeature {
    bool stateOn = true;
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
        writeCmd(state ? 1 : 0);
        stateOn = state;
    }
    // Read LED state [HIGH:LOW] (on / off)
    int isOn() {
        return stateOn;
    }
};
};

class Module22 : public TotemModuleX {
public:
    Features22::Color color;
    Features22::Get colorR, colorG, colorB;
    Features22::Get IR, lumen;
    Features22::Temp  temp;
    Features22::TempNTC  ntc;
    Features22::Get humidity;
    Features22::Pressure pressure;
    Features22::Altitude altitude;
    Features22::Led led;
    // Set current pressure at sea level (Pascal)
    void setSeaLevel(uint32_t pressurePa) {
        module.write(C("altitude/seaLevel"), pressurePa);
    }
    // Change light sensor gain
    void setLightSensorGain(uint8_t gain) {
        module.write(C("light/gain"), gain);
    }

    Module22(uint16_t serial = 0) : TotemModuleX(22, serial),
    color(this, C("color")),
    colorR(this, C("color/R")), colorG(this, C("color/G")), colorB(this, C("color/B")),
    IR(this, C("light/IR")), lumen(this, C("light/lumen")),
    temp(this, C("temperature/C")), ntc(this, C("ntc/C")),
    humidity(this, C("humidity")),
    pressure(this, C("pressure/Pa")),
    altitude(this, C("altitude/ft")),
    led(this, C("led"))
    { }
};

#endif /* MODULE22 */
