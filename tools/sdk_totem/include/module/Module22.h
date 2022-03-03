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
#ifndef MODULE22
#define MODULE22

#include "lib/TotemEventModule.h"

namespace Features22 {
using namespace Feature;
namespace cmd {
enum Commands {
    color              = CMD("color"),
    color_R            = CMD("color/R"),
    color_G            = CMD("color/G"),
    color_B            = CMD("color/B"),
    light_IR           = CMD("light/IR"),
    light_lumen        = CMD("light/lumen"),
    light_gain         = CMD("light/gain"),
    ntc                = CMD("ntc"),
    ntc_C              = CMD("ntc/C"),
    ntc_F              = CMD("ntc/F"),
    ntc_K              = CMD("ntc/K"),
    ntc_R              = CMD("ntc/R"),
    temperature        = CMD("temperature"),
    temperature_C      = CMD("temperature/C"),
    temperature_F      = CMD("temperature/F"),
    temperature_K      = CMD("temperature/K"),
    humidity           = CMD("humidity"),
    pressure           = CMD("pressure"),
    pressure_mbar      = CMD("pressure/mbar"),
    pressure_Pa        = CMD("pressure/Pa"),
    pressure_hPa       = CMD("pressure/hPa"),
    pressure_psi       = CMD("pressure/psi"),
    altitude           = CMD("altitude"),
    altitude_m         = CMD("altitude/m"),
    altitude_ft        = CMD("altitude/ft"),
    altitude_seaLevel  = CMD("altitude/seaLevel"),
    led                = CMD("led"),
};
} // namespace cmd
class Color : public SingleEvent {
    const uint32_t events[3] = {cmd::color_R, cmd::color_G, cmd::color_B};
public:
    Color(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get Red color amount [0:262143]
    uint32_t getRed() {
        return this->getCmd(cmd::color_R).getInt();
    }
    // Get Green color amount [0:262143]
    uint32_t getGreen() {
        return this->getCmd(cmd::color_G).getInt();
    }
    // Get Blue color amount [0:262143]
    uint32_t getBlue() {
        return this->getCmd(cmd::color_B).getInt();
    }
};
class Light : public SingleEvent {
    const uint32_t events[2] = {cmd::light_IR, cmd::light_lumen};
public:
    Light(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get Infrared light amount [0:262143]
    uint32_t getIR() {
        return this->getCmd(cmd::light_IR).getInt();
    }
    // Get Luminosity amount [0:262143]
    uint32_t getLumen() {
        return this->getCmd(cmd::light_lumen).getInt();
    }
};
class Temp : public SingleEvent {
    const uint32_t events[2] = {cmd::temperature_C, cmd::humidity};
public:
    Temp(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get temperature in Celsius
    float getC() {
        float value = this->getCmd(cmd::temperature_C).getInt();
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
        return this->getCmd(cmd::humidity).getInt();
    }
};
class TempNTC : public SingleEvent {
    const uint32_t events[2] = {cmd::ntc_C, cmd::ntc_R};
public:
    TempNTC(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get temperature in Celsius
    float getC() {
        float value = this->getCmd(cmd::ntc_C).getInt();
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
        return this->getCmd(cmd::ntc_R).getInt();
    }
};
class Pressure : public SingleEvent {
    const uint32_t events[1] = {cmd::pressure_Pa};
public:
    Pressure(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get pressure in Pa (Pascal)
    float getPa() {
        return this->getCmd(cmd::pressure_Pa).getInt();
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
};
class Altitude : public SingleEvent {
    const uint32_t events[1] = {cmd::altitude_ft};
public:
    Altitude(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get altitude in M (Meter)
    float getMeter() {
        return this->getFoot() * 0.3048f;
    }
    // Get altitude in Ft (Foot)
    float getFoot() {
        return this->getCmd(cmd::altitude_ft).getInt();
    }
    // Get altitude in in (Inch)
    float getInch() {
        return this->getFoot() * 12;
    }
};
class Led : public NoEvent {
    uint8_t ledState = 0;
public:
    Led(TotemModuleData &d) : NoEvent(d) { }
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
        writeCmd(cmd::led, state ? 1 : 0);
        ledState = state;
    }
    // Read LED state [HIGH:LOW] (on / off)
    int isOn() {
        return ledState;
    }
};
} // namespace Features22

class Module22 : public Feature::TotemEventModule {
    Feature::Event eventsList[11] = {
        cmd::color_R,
        cmd::color_G,
        cmd::color_B,
        cmd::light_IR,
        cmd::light_lumen,
        cmd::temperature_C,
        cmd::humidity,
        cmd::ntc_C,
        cmd::ntc_R,
        cmd::pressure_Pa,
        cmd::altitude_ft,
    };
public:
    using cmd = Features22::cmd::Commands;
    Features22::Color color;
    Features22::Light light;
    Features22::Temp  temp;
    Features22::TempNTC  ntc;
    Features22::Pressure pressure;
    Features22::Altitude altitude;
    Features22::Led led;

    // Change light sensor gain
    void setLightSensorGain(uint8_t gain) {
        data.module.write(cmd::light_gain, gain);
    }
    // Set current pressure at sea level (Pascal)
    void setSeaLevel(uint32_t pressurePa) {
        data.module.write(cmd::altitude_seaLevel, pressurePa);
    }
    
    Module22(uint16_t serial = 0) : Feature::TotemEventModule(22, serial, eventsList),
    color(data), light(data), temp(data), ntc(data), pressure(data), altitude(data), led(data)
    { }
};

#endif /* MODULE22 */
