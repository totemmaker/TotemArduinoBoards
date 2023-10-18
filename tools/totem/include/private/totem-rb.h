/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_RB
#define INCLUDE_TOTEM_RB

#include <stdint.h>

namespace _Totem {

class RoboBoard {
public:
    RoboBoard();
    ///////////////////////
    //   Board control
    ///////////////////////
    // Is USB cable connected
    bool isUSB();
    ///////////////////////
    //   Get versions
    ///////////////////////
    // Get RoboBoard number
    int getNumber();
    // Get RoboBoard revision
    int getRevision();
    // Get X4 driver (co-processor) firmware version number
    int getDriverVersion();
    // Enable 3.3V LDO (RoboBoard X3 only)
    void setEnable3V3(bool state);

/*******************************
          RB.battery
*******************************/
class Battery {
public:
    ///////////////////////
    // Read battery state
    ///////////////////////
    // Get battery voltage [2800:4200] or [8400:12600]
    int getVoltage();
    // Get battery current [-2000:2000]
    int getCurrent();
    // Is battery charging
    bool isCharging();
};
/*******************************
          RB.button
*******************************/
class Button {
public:
    // Get button state [0:1]
    int getState();
};
/*******************************
          RB.led
*******************************/
class Led {
public:
    // Set LED state [`0`:`1`]
    void setState(uint8_t state);
};
/*******************************
          RB.rgbX
*******************************/
class RGBStrip {
protected:
    const int8_t port;
public:
    // Set LED with HEX color code [`0`:`0xFFFFFF`]
    void colorHEX(uint32_t hex); // hex [`0`:`0xFFFFFF`]
    // Set LED fade with HEX color code [`0`:`0xFFFFFF`]
    void fadeColorHEX(uint32_t hex); // hex [`0`:`0xFFFFFF`]
    // Start LED port fading
    void fadeStart(uint32_t duration);
    // Write updated color to LED
    void update();
    // Enable RGB LED
    void setEnable(bool state);

    RGBStrip(int8_t port) : port(port) { }
};
/*******************************
          RB.rgb
*******************************/
class RGBStripGroup : public RGBStrip {
public:
    // Access RGB LED with numeric index. RB.rgb[0] references RB.rgbA
    RGBStrip& operator[](int num);

    RGBStripGroup() : RGBStrip(-1) {}
};
/*******************************
          RB.dcX
*******************************/
class DC {
protected:
    const int8_t port;
public:
    ///////////////////////
    //   Power control
    ///////////////////////
    // Spin motor at specified power and direction
    // Negative - backwards. `0` - stop
    // `spinPower`: output power [`-100`:`100`]
    void power(int spinPower);
    // Brake motor at specified power
    // `brakePower`: braking power [`0`:`100`]
    void brake(int brakePower);
    ///////////////////////
    //  Tone generator
    ///////////////////////
    // Play specified frequency on DC port group
    // `frequency`: tone frequency [`0`:`20000`] Hz
    // `duration`: (optional) stop playing after time (milliseconds)
    void tone(uint32_t frequency, uint32_t duration);
    // Enable DC port
    void setEnable(bool enable);
    // Set DC port group PWM frequency (default 50Hz)
    // `frequency`: PWM frequency [`1`:`250000`] Hz
    void setFrequency(uint32_t frequency);
    // Set decay mode to fast
    void setFastDecay(bool state);

    DC(int8_t port) : port(port) {}
};
/*******************************
          RB.dc
*******************************/
class DCGroup : public DC {
public:
    // Access DC port with numeric index. RB.dc[0] references RB.dcA
    DC& operator[](int port);

    DCGroup() : DC(-1) {}
};
/*******************************
          RB.servoX
*******************************/
class Servo {
protected:
    const int8_t port;
public:
    // Turn motor to pulse [`0`:`period`] in microseconds (us). Typical: [500:2500]
    void pulse(uint32_t pulse, uint32_t duration);
    // Set constant Servo motor speed RPM (Rounds-Per-Minute)
    void setSpeedRPM(float rpm); // RPM
    // Enable DC port
    void setEnable(bool enable);
    // Set Servo period [`1`:`65535`] us (microseconds). Default: 20000us (50Hz)
    void setPeriod(uint32_t period);

    Servo(int8_t port) : port(port) {}
};
/*******************************
          RB.servo
*******************************/
class ServoGroup : public Servo {
public:
    // Access Servo port with numeric index. RB.servo[0] references RB.servoA
    Servo& operator[](int port);

    ServoGroup() : Servo(-1) {}
};

    Battery battery;
    Button button;
    Led led;
    RGBStripGroup rgb;
    RGBStrip rgbA, rgbB, rgbC, rgbD;
    DCGroup dc;
    DC dcA, dcB, dcC, dcD;
    ServoGroup servo;
    Servo servoA, servoB, servoC;

}; // class RoboBoard

} // namespace Totem

extern _Totem::RoboBoard RB;

#endif /* INCLUDE_TOTEM_RB */
