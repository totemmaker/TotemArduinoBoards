/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE_22
#define INCLUDE_TOTEM_MODULE_22

#ifdef ARDUINO_ROBOBOARD_X4

#include "private_module/totem-event-module.h"

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
class Led {
    TotemModule &m;
    uint8_t ledState = 1;
public:
    Led(TotemModule &m) : m(m) { }
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
        m.write(cmd::led, state ? 1 : 0);
        ledState = state;
    }
    // Read LED state [HIGH:LOW] (on / off)
    int isOn() {
        return ledState;
    }
};
} // namespace Features22

class TotemModule22 : public Feature::TotemEventModule {
public:
    // Available TotemModule22 events registered with addEvent() function
    enum {
        evtColor = 22 << 16,
        evtIR = evtColor + 3,
        evtLumen,
        evtTemp,
        evtNtc,
        evtHumidity,
        evtPressure,
        evtAltitude,
    };
    using cmd = Features22::cmd::Commands;
    // LED control
    Features22::Led led;

    // Get Red color amount [0:262143]
    uint32_t getColorR() { return readCmdInt(cmd::color_R); }
    // Get Green color amount [0:262143]
    uint32_t getColorG() { return readCmdInt(cmd::color_G); }
    // Get Blue color amount [0:262143]
    uint32_t getColorB() { return readCmdInt(cmd::color_B); }
    // Get Infrared light amount [0:262143]
    uint32_t getIR() { return readCmdInt(cmd::light_IR); }
    // Get Luminosity amount [0:262143]
    uint32_t getLumen() { return readCmdInt(cmd::light_lumen); }

    // Get humidity [0:100]%
    uint8_t getHumidity() { return readCmdInt(cmd::humidity); }

    // Get temperature in Celsius
    float getTempC() { return ((float) readCmdInt(cmd::temperature_C)) / 100; };
    // Get temperature in Fahrenheit
    float getTempF() { return getTempC() * 9 / 5 + 32; }
    // Get temperature in Kelvin
    float getTempK() { return getTempC() + 273.15; }

    // Get NTC temperature in Celsius
    float getNtcC() { return ((float) readCmdInt(cmd::ntc_C)) / 100; };
    // Get NTC temperature in Fahrenheit
    float getNtcF() { return getNtcC() * 9 / 5 + 32; }
    // Get NTC temperature in Kelvin
    float getNtcK() { return getNtcC() + 273.15; }
    // Get NTC sensor resistance
    uint32_t getNtcResistance() { return readCmdInt(cmd::ntc_R); }

    // Get pressure in Pa (Pascal)
    float getPressurePa() { return readCmdInt(cmd::pressure_Pa); };
    // Get pressure in hPa (hectopascal)
    float getPressurehPa() { return getPressurePa() / 100; }
    // Get pressure in mbar (milibar)
    float getPressureMbar() { return getPressurePa() / 100; }
    // Get pressure in Bar (Bar)
    float getPressureBar() { return getPressurePa() / 100000; }
    // Get pressure in PSI (Pounds per square inch)
    float getPressurePsi() { return getPressurePa() / 6895; }

    // Get altitude in M (Meter)
    float getAltitudeMeter() { return getAltitudeFoot() * 0.3048; }
    // Get altitude in Ft (Foot)
    float getAltitudeFoot() { return readCmdInt(cmd::altitude_ft); }
    // Get altitude in in (Inch)
    float getAltitudeInch() { return getAltitudeFoot() * 12; }

    // Set current pressure at sea level (Pascal)
    void setAltitudeSeaLevel(uint32_t pressurePa) {
        writeCmdInt(cmd::altitude_seaLevel, pressurePa);
    }

    // Change light sensor gain
    void setLightSensorGain(uint8_t gain) {
        writeCmdInt(cmd::light_gain, gain);
    }

    TotemModule22(uint16_t serial = 0) : Feature::TotemEventModule(22, serial, eventsList),
    led(module)
    { }
private:
    void callEventHandler(int evt) override {
        if (evt == evtColor+1 || evt == evtColor+2) evt = evtColor;
        Feature::TotemEventModule::callEventHandler(evt);
    }

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
};

#else /* ARDUINO_ROBOBOARD_X4 */
#error "TotemModule22 is only supported with RoboBoard X4"
#endif

#endif /* INCLUDE_TOTEM_MODULE_22 */
