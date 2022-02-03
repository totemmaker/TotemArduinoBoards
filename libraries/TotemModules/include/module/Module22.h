#ifndef MODULE22
#define MODULE22

#include "lib/TotemEventModule.h"

namespace Features22 {
class Light : public Feature::MultiEventHidden {
    const uint32_t cmdList[5] = {
        Feature::CMD("color/R"), Feature::CMD("color/G"), Feature::CMD("color/B"),
        Feature::CMD("light/IR"), Feature::CMD("light/lumen")
    };
public:
    Light(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get Red color amount [0:262143]
    uint32_t getRed() {
        return this->getCmd(0)->getInt();
    }
    // Get Green color amount [0:262143]
    uint32_t getGreen() {
        return this->getCmd(1)->getInt();
    }
    // Get Blue color amount [0:262143]
    uint32_t getBlue() {
        return this->getCmd(2)->getInt();
    }
    // Get Infrared light amount [0:262143]
    uint32_t getIR() {
        return this->getCmd(3)->getInt();
    }
    // Get Luminosity amount [0:262143]
    uint32_t getLumen() {
        return this->getCmd(4)->getInt();
    }
    // Change light sensor gain
    void setLightSensorGain(uint8_t gain) {
        writeCustomCmd(Feature::CMD("light/gain"), gain);
    }
    // Event Red
    bool isEventRed() { return this->isEvent(0); }
    void eventRed() { this->event(0); }
    void eventRed(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOnceRed() { this->eventOnce(0); }
    // Event Green
    bool isEventGreen() { return this->isEvent(1); }
    void eventGreen() { this->event(1); }
    void eventGreen(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceGreen() { this->eventOnce(1); }
    // Event Blue
    bool isEventBlue() { return this->isEvent(2); }
    void eventBlue() { this->event(2); }
    void eventBlue(uint32_t intervalMs) { this->event(2, intervalMs); }
    void eventOnceBlue() { this->eventOnce(2); }
    // Event Infrared
    bool isEventIR() { return this->isEvent(3); }
    void eventIR() { this->event(3); }
    void eventIR(uint32_t intervalMs) { this->event(3, intervalMs); }
    void eventOnceIR() { this->eventOnce(3); }
    // Event Luminosity
    bool isEventLumen() { return this->isEvent(4); }
    void eventLumen() { this->event(4); }
    void eventLumen(uint32_t intervalMs) { this->event(4, intervalMs); }
    void eventOnceLumen() { this->eventOnce(4); }
};
class Temp : public Feature::MultiEventHidden {
    const uint32_t cmdList[2] = {
        Feature::CMD("temperature/C"), Feature::CMD("humidity")
    };
public:
    Temp(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get temperature in Celsius
    float getC() {
        float value = this->getCmd(0)->getInt();
        return value / 100;
    }
    // Get temperature in Farenheit
    float getF() {
        return this->getC() * 9 / 5 + 32;
    }
    // Get temperature in Kelvin
    float getK() {
        return this->getC() + 273.15f;
    }
    // Get humidity [0:100]%
    uint8_t getHumidity() {
        return this->getCmd(1)->getInt();
    }
    // Event Temperature
    bool isEventTemperature() { return this->isEvent(0); }
    void eventTemperature() { this->event(0); }
    void eventTemperature(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOnceTemperature() { this->eventOnce(0); }
    // Event Humidity
    bool isEventHumidity() { return this->isEvent(1); }
    void eventHumidity() { this->event(1); }
    void eventHumidity(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceHumidity() { this->eventOnce(1); }
};
class TempNTC : public Feature::MultiEventHidden {
    const uint32_t cmdList[2] = {
        Feature::CMD("nfc/C"), Feature::CMD("nfc/R")
    };
public:
    TempNTC(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get temperature in Celsius
    float getC() {
        float value = this->getCmd(0)->getInt();
        return value / 100;
    }
    // Get temperature in Farenheit
    float getF() {
        return this->getC() * 9 / 5 + 32;
    }
    // Get temperature in Kelvin
    float getK() {
        return this->getC() + 273.15f;
    }
    // Get NTC sensor resistance
    uint32_t getResistance() {
        return this->getCmd(1)->getInt();
    }
    // Event Temperature
    bool isEventTemperature() { return this->isEvent(0); }
    void eventTemperature() { this->event(0); }
    void eventTemperature(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOnceTemperature() { this->eventOnce(0); }
    // Event Resistance
    bool isEventResistance() { return this->isEvent(1); }
    void eventResistance() { this->event(1); }
    void eventResistance(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceResistance() { this->eventOnce(1); }
};
class Pressure : public Feature::MultiEventHidden {
    const uint32_t cmdList[2] = {
        Feature::CMD("pressure/Pa"), Feature::CMD("altitude/ft")
    };
public:
    Pressure(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get pressure in Pa (Pascal)
    float getPa() {
        return this->getCmd(0)->getInt();
    }
    // Get pressure in hPa (hectopascal)
    float gethPa() {
        return this->getPa() / 100;
    }
    // Get pressure in mbar (milibar)
    float getMbar() {
        return this->getPa() / 100;
    }
    // Get pressure in Bar (Bar)
    float getBar() {
        return this->getPa() / 100000;
    }
    // Get pressure in PSI (Pounds per square inch)
    float getPsi() {
        return this->getPa() / 6895;
    }
    // Get altitude in M (Meter)
    float getAltMeter() {
        return this->getAltFoot() * 0.3048f;
    }
    // Get altitude in Ft (Foot)
    float getAltFoot() {
        return this->getCmd(1)->getInt();
    }
    // Get altitude in in (Inch)
    float getAltInch() {
        return this->getAltFoot() * 12;
    }
    // Set current pressure at sea level (Pascal)
    void setSeaLevel(uint32_t pressurePa) {
        writeCustomCmd(Feature::CMD("altitude/seaLevel"), pressurePa);
    }
    // Event Pressure
    bool isEventPressure() { return this->isEvent(0); }
    void eventPressure() { this->event(0); }
    void eventPressure(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOncePressure() { this->eventOnce(0); }
    // Event Altitude
    bool isEventAltitude() { return this->isEvent(1); }
    void eventAltitude() { this->event(1); }
    void eventAltitude(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceAltitude() { this->eventOnce(1); }
};
class Led : public Feature::Simple {
    uint8_t ledState = 0;
    const uint32_t cmdList[1] = {
        Feature::CMD("led")
    };
public:
    Led(TotemModuleData &d) : Feature::Simple(d, cmdList) { }
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
        writeChannel(0, state ? 1 : 0);
        ledState = state;
    }
    // Read LED state [HIGH:LOW] (on / off)
    int isOn() {
        return ledState;
    }
};
};

class Module22 : public TotemEventModule {
public:
    Features22::Light light;
    Features22::Temp  temp;
    Features22::TempNTC  ntc;
    Features22::Pressure pressure;
    Features22::Led led;
    
    Module22(uint16_t serial = 0) : TotemEventModule(22, serial),
    light(data), temp(data), ntc(data), pressure(data), led(data)
    { }
};

#endif /* MODULE22 */
