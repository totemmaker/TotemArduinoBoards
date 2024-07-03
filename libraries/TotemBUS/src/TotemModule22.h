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

#include "private_module/totem-x4-module.h"

namespace Features22 {
namespace cmd {
enum Commands {
    color              = 0x3d7e6258, //CMD("color"),
    color_R            = 0x94b09e05, //CMD("color/R"),
    color_G            = 0x9fb0af56, //CMD("color/G"),
    color_B            = 0xa4b0b735, //CMD("color/B"),
    light_IR           = 0xd8b6633b, //CMD("light/IR"),
    light_lumen        = 0x1c8e34a9, //CMD("light/lumen"),
    light_gain         = 0x6b98d143, //CMD("light/gain"),
    ntc                = 0x3c74e4b4, //CMD("ntc"),
    ntc_C              = 0x8d1a07e6, //CMD("ntc/C"),
    ntc_F              = 0x921a0fc5, //CMD("ntc/F"),
    ntc_K              = 0x951a147e, //CMD("ntc/K"),
    ntc_R              = 0x9e1a22a9, //CMD("ntc/R"),
    temperature        = 0xe9f2a935, //CMD("temperature"),
    temperature_C      = 0x86515957, //CMD("temperature/C"),
    temperature_F      = 0x81515178, //CMD("temperature/F"),
    temperature_K      = 0x7e514cbf, //CMD("temperature/K"),
    humidity           = 0x25c5b9a0, //CMD("humidity"),
    pressure           = 0xcfa8a3a2, //CMD("pressure"),
    pressure_mbar      = 0xb07c67d7, //CMD("pressure/mbar"),
    pressure_Pa        = 0x95aaa7cc, //CMD("pressure/Pa"),
    pressure_hPa       = 0xd5ea2ab2, //CMD("pressure/hPa"),
    pressure_psi       = 0xa1d802b1, //CMD("pressure/psi"),
    altitude           = 0x527d2af7, //CMD("altitude"),
    altitude_m         = 0x3e7214ff, //CMD("altitude/m"),
    altitude_ft        = 0xd6adacfa, //CMD("altitude/ft"),
    altitude_seaLevel  = 0x7fd6bcc7, //CMD("altitude/seaLevel"),
    led                = 0x406aeaca, //CMD("led"),
};
} // namespace cmd
class Led {
    _Totem::TotemModule &m;
    uint8_t ledState = 1;
public:
    Led(_Totem::TotemModule &m) : m(m) { }
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

class TotemModule22 : public TotemX4Module {
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

    TotemModule22(uint16_t serial = 0) : TotemX4Module(22, serial, eventsList),
    led(module)
    { }
private:
    void callEventHandler(int evt) override {
        if (evt == evtColor+1 || evt == evtColor+2) evt = evtColor;
        TotemX4Module::callEventHandler(evt);
    }

    _Totem::Event eventsList[11] = {
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
