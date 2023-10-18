/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_DC
#define INCLUDE_TOTEM_DC

namespace _Totem {

class SingleDCClass {
    const uint8_t port;
public:
    ///////////////////////
    //   Power control
    ///////////////////////

    /// @brief Spin motor at specified power and direction
    /// @param spinPower [-100:100]% power. 0 - stop
    void spin(int spinPower);
    /// @brief Brake motor at specified power
    /// @param brakePower [0:100]% braking power
    void brake(int brakePower = 100);
    /// @brief Power off motor and let it free spin
    void coast();
    /// @brief Read DC port power
    /// @return [-100:100]% spin power
    int getSpin();
    /// @brief Read DC port braking power
    /// @return [0:100]% braking power
    int getBrake();

    ///////////////////////
    //  Tone generator
    ///////////////////////

    void tone(uint32_t frequency);
    /// @brief Play specified frequency on DC port group
    /// @param frequency [0:20000]Hz tone frequency
    /// @param duration (optional) stop playing after time (milliseconds)
    void tone(uint32_t frequency, uint32_t duration);
    /// @brief Get DC port tone frequency
    /// @return [0:20000]Hz tone frequency
    int getTone();

    ///////////////////////
    // Acceleration control
    ///////////////////////

    /// @brief Check if motor is currently in acceleration or deceleration phase
    /// @return [true:false] is accelerating
    bool isAccelerating();
    /// @brief Wait for motor to reach applied power (speed). Used with acceleration and deceleration enabled
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - target speed reached. false - timeout
    bool wait(uint32_t timeout = 0);
    /// @brief Set time required to accelerate from 0 to 100%
    /// @param ms time in milliseconds
    void setAccelerationTime(uint32_t ms);
    /// @brief Set time required to decelerate from 100% to 0
    /// @param ms time in milliseconds
    void setDecelerationTime(uint32_t ms);
    /// @brief Read configured acceleration time
    /// @return time in milliseconds
    int getAccelerationTime();
    /// @brief Read configured deceleration time
    /// @return time in milliseconds
    int getDecelerationTime();

    ///////////////////////
    //   Configuration
    ///////////////////////

    /// @brief Enable motor DC peripheral
    /// @param enable [true:false] is enabled
    void setEnable(bool enable);
    /// @brief Set inverted motor spin direction
    /// @param state false - normal. true - invert
    void setInvert(bool state);
    /// @brief Set DC autobrake power (when power is set to 0)
    /// @param power [0:100]% or [true:false]. 0 - off (coast)
    void setAutobrake(int power);
    void setAutobrake(bool state) { setAutobrake(state ? 100 : 0); }
    /// @brief Set DC port group PWM frequency (default 50Hz)
    /// @param frequency [1:250000]Hz PWM frequency
    void setFrequency(uint32_t frequency);
    /// @brief Configure motor min and max power range
    /// @param powerMin [0:100] (default 10)
    /// @param powerMax [0:100] (default 100)
    void setRange(uint32_t powerMin, uint32_t powerMax);
    /// @brief Change to fast decay mode
    /// @param state (false) slow decay, (true) fast decay
    void setFastDecay(bool state);
    /// @brief Check if motor DC peripheral is enabled
    /// @return [true:false] is enabled
    bool getEnable();
    /// @brief Check if DC port is inverted
    /// @return [true:false] is inverted
    bool getInvert();
    /// @brief Read configured DC port autobrake power
    /// @return [0:100]% autobrake power
    int getAutobrake();
    /// @brief Read configured DC port group PWM frequency (default 50Hz)
    /// @return [1:250000]Hz
    int getFrequency();
    // Range struct
    struct Range {
        int min, max;
    };
    /// @brief Read configured motor power range
    /// @return struct Range
    Range getRange();
    /// @brief Check if fast decay mode is selected
    /// @return (true) fast decay, (false) slow decay
    bool getFastDecay();

    int getType();
    int getPort(int idx = 0);

    SingleDCClass(uint8_t port);
};

class DCClass {
public:
    ///////////////////////
    //   Power control
    ///////////////////////

    /// @brief Spin motor at specified power and direction
    /// @param spinPower [-100:100]% power. 0 - stop
    void spin(int spinPower);
    /// @brief Brake motor at specified power
    /// @param brakePower [0:100]% braking power
    void brake(int brakePower = 100);
    /// @brief Power off motor and let it free spin
    void coast();

    ///////////////////////
    //  Tone generator
    ///////////////////////

    /// @brief Play specified frequency on DC port group
    /// @param frequency [0:20000]Hz tone frequency
    /// @param duration (optional) stop playing after time (milliseconds)
    void tone(uint32_t frequency, uint32_t duration = 0);

    ///////////////////////
    // Acceleration control
    ///////////////////////
    
    /// @brief Check if motor is currently in acceleration or deceleration phase
    /// @return [true:false] is accelerating
    bool isAccelerating();
    /// @brief Wait for motor to reach applied power (speed). Used with acceleration and deceleration enabled
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - target speed reached. false - timeout
    bool wait(uint32_t timeout = 0);
    /// @brief Set time required to accelerate from 0 to 100%
    /// @param ms time in milliseconds
    void setAccelerationTime(uint32_t ms);
    /// @brief Set time required to decelerate from 100% to 0
    /// @param ms time in milliseconds
    void setDecelerationTime(uint32_t ms);

    ///////////////////////
    //   Configuration
    ///////////////////////

    /// @brief Enable motor DC peripheral
    /// @param enable [true:false] is enabled
    void setEnable(bool enable);
    /// @brief Set inverted motor spin direction
    /// @param state false - normal. true - invert
    void setInvert(bool state);
    /// @brief Set DC autobrake power (when power is set to 0)
    /// @param power [0:100]% or [true:false]. 0 - off (coast)
    void setAutobrake(int power);
    void setAutobrake(bool state) { setAutobrake(state ? 100 : 0); }
    /// @brief Set DC port group PWM frequency (default 50Hz)
    /// @param frequency [1:250000]Hz PWM frequency
    void setFrequency(uint32_t frequency);
    /// @brief Configure motor min and max power range
    /// @param powerMin [0:100] (default 10)
    /// @param powerMax [0:100] (default 100)
    void setRange(uint32_t powerMin, uint32_t powerMax);
    /// @brief Change to fast decay mode
    /// @param state (false) slow decay, (true) fast decay
    void setFastDecay(bool state);

    /// @brief Access DC motor A control interface
    SingleDCClass A;
    /// @brief Access DC motor B control interface
    SingleDCClass B;
    /// @brief Access DC motor C control interface
    SingleDCClass C;
    /// @brief Access DC motor D control interface
    SingleDCClass D;
    /// @brief Access specific DC motor with array index
    /// @param num [0:3] array index
    /// @return single DC motor control interface
    SingleDCClass& operator[](int num);

    DCClass();
};

} // namespace _Totem

extern _Totem::DCClass DC;

#endif /* INCLUDE_TOTEM_DC */
