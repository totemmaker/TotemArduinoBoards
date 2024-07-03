/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_SERVO
#define INCLUDE_TOTEM_SERVO

namespace totem {

struct ServoSequence {
    uint32_t delay;
    int position;
};

} // namespace totem

namespace _Totem {

class SingleServoClass {
    const uint8_t port;
public:
    ///////////////////////
    //  Position control
    ///////////////////////

    /// @brief Turn motor arm to position within exact time frame
    /// @param position [-100:100]%. 0 - center
    /// @param duration change position with duration in ms
    void spinPosDuration(int position, uint32_t duration);
    /// @brief Turn motor arm to position with exact speed
    /// @param position [-100:100]%. 0 - center
    /// @param rpm change position with speed [1:60] (RPM)
    void spinPosRPM(int position, uint32_t rpm);
    /// @brief Turn motor arm to position
    /// @param position [-100:100]%. 0 - center
    void spinPos(int position) { spinPosDuration(position, 0); }
    /// @brief Turn motor arm to angle degrees within exact time frame
    /// @param angle [0:180]deg
    /// @param duration change position with duration in ms
    void spinAngleDuration(uint32_t angle, uint32_t duration);
    /// @brief Turn motor arm to angle degrees with exact speed
    /// @param angle [0:180]deg
    /// @param rpm change position with speed [1:60] (RPM)
    void spinAngleRPM(uint32_t angle, uint32_t rpm);
    /// @brief Turn motor arm to angle degrees
    /// @param angle [0:180]deg
    void spinAngle(uint32_t angle) { spinAngleDuration(angle, 0); }
    /// @brief Turn motor arm to exact pulse (microseconds) within exact time frame
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    /// @param duration change position with duration in ms
    void spinPulseDuration(uint32_t pulse, uint32_t duration);
    /// @brief Turn motor arm to exact pulse (microseconds) with exact speed
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    /// @param rpm change position with speed [1:60] (RPM)
    void spinPulseRPM(uint32_t pulse, uint32_t rpm);
    /// @brief Turn motor arm to exact pulse (microseconds)
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    void spinPulse(uint32_t pulse) { spinPulseDuration(pulse, 0); }
    /// @brief Set exact pulse output without any conversion and limit checking
    /// @param pulse [0:period]us
    void spinPulseRaw(uint32_t pulse);
    /// @brief Release motor from holding it's position (free spin). Turns off PWM signal. Not all motors may support this
    void coast();
    /// @brief Read motor position %
    /// @return [-100:100]% position. 0 - center
    int getPos();
    /// @brief Read motor position angle degrees
    /// @return [0:180]deg. 90 - center
    int getAngle();
    /// @brief Read motor position in microseconds 
    /// @return [0:period]us
    int getPulse();

    ///////////////////////
    //   Speed control
    ///////////////////////
    
    /// @brief Set constant Servo motor speed RPM (Rounds-Per-Minute)
    /// @param rpm Typically: [1:60]
    void setSpeedRPM(uint32_t rpm);
    /// @brief Set constant Servo motor speed sec/60deg (seconds / 60 degree)
    /// @param seconds Typically: [0.09:0.18] sec/60deg
    void setSpeedS60(float seconds);
    /// @brief Read Servo port speed limit
    /// @return RPM (Rounds-Per-Minute)
    int getSpeedRPM();
    /// @brief Read Servo port speed limit
    /// @return  sec/60deg (seconds / 60 degree)
    float getSpeedS60();

    ///////////////////////
    // Sequence execution
    ///////////////////////

    /// @brief Run movements sequence
    /// @param seq array list of moves
    /// @param times (optional) number of times to run (0 - repeat)
    template<int SIZE>
    void run(const totem::ServoSequence (&seq)[SIZE], uint32_t times = 1) {
        run(seq, SIZE, times);
    }
    
    /// @brief Check if motor is moving
    /// @return [true:false] is moving 
    bool isMoving();
    /// @brief Wait till motor reaches position
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - reached position. false - timeout
    bool wait(uint32_t timeout = 0);
    /// @brief Stop motor move
    void stop();

    ///////////////////////
    //   Configuration
    ///////////////////////
    
    /// @brief Enable Servo peripheral
    /// @param enable [true:false] is enabled
    void setEnable(bool enable);
    /// @brief Set inverted motor spin direction
    /// @param state false - normal. true - invert
    void setInvert(bool state);
    /// @brief Set Servo signal PWM period. Default: 20000us (50Hz)
    /// @param period [1:65535] us (microseconds)
    [[deprecated("Use Servo.setPeriod()")]]
    void setPeriod(uint32_t period);
    /// @brief Set Servo motor configuration. Default: 180deg, 500us, 2500us
    /// @param angleMax 180 or 270 degrees
    /// @param usMin [0:period]us pulse (500)
    /// @param usMax [0:period]us pulse (2500)
    void setMotor(uint32_t angleMax, uint32_t usMin, uint32_t usMax);
    /// @brief Trim servo motor endpoints [-100:100]%
    /// @param left amount of steer to left. Default: -100
    /// @param center center adjustment. Default: 0
    /// @param right amount of steer to right. Default: 100
    void setTrim(int left, int center, int right);
    void setTrim(int left, int right) { setTrim(left, (left+right)/2, right); }
    /// @brief Trim servo motor endpoints precisely with pulse (us)
    /// @param min [0:period]us pulse (500)
    /// @param center [0:period]us pulse (1500)
    /// @param max [0:period]us pulse (2500)
    void setTrimPulse(uint32_t min, uint32_t center, uint32_t max);
    void setTrimPulse(uint32_t min, uint32_t max) { setTrimPulse(min, (min+max)/2, max); }
    /// @brief Check if Servo port peripheral is enabled
    /// @return [true:false] is enabled
    bool getEnable();
    /// @brief Check if Servo port is inverted
    /// @return [true:false] is inverted
    bool getInvert();
    /// @brief Read configured Servo period (us)
    /// @return [1:65535] us (microseconds)
    [[deprecated("Use Servo.getPeriod()")]]
    int getPeriod();
    // MotorType struct
    struct MotorType {
        int angle;
        int usMin;
        int usMax;
    };
    // Range struct
    struct Range {
        int min, mid, max;
    };
    /// @brief Read motor configuration
    /// @return angle, usMin, usMax - angle (degrees), pulse (us), pulse (us)
    MotorType getMotor();
    /// @brief Read configured servo position limit [-100:100]
    /// @return min, mid, max - left, center, right
    Range getTrim();
    /// @brief Read configured servo pulse limit [0:period]
    /// @return min, mid, max - left, center, right
    Range getTrimPulse();

    int getPort();

    SingleServoClass(uint8_t port);
private:
    void run(const totem::ServoSequence seq[], uint32_t size, uint32_t times);
};

class ServoClass {
public:
    ///////////////////////
    //  Position control
    ///////////////////////

    /// @brief Turn motor arm to position within exact time frame
    /// @param position [-100:100]%. 0 - center
    /// @param duration change position with duration in ms
    void spinPosDuration(int position, uint32_t duration);
    /// @brief Turn motor arm to position with exact speed
    /// @param position [-100:100]%. 0 - center
    /// @param rpm change position with speed [1:60] (RPM)
    void spinPosRPM(int position, uint32_t rpm);
    /// @brief Turn motor arm to position
    /// @param position [-100:100]%. 0 - center
    void spinPos(int position) { spinPosDuration(position, 0); }
    /// @brief Turn motor arm to angle degrees within exact time frame
    /// @param angle [0:180]deg
    /// @param duration change position with duration in ms
    void spinAngleDuration(uint32_t angle, uint32_t duration);
    /// @brief Turn motor arm to angle degrees with exact speed
    /// @param angle [0:180]deg
    /// @param rpm change position with speed [1:60] (RPM)
    void spinAngleRPM(uint32_t angle, uint32_t rpm);
    /// @brief Turn motor arm to angle degrees
    /// @param angle [0:180]deg
    void spinAngle(uint32_t angle) { spinAngleDuration(angle, 0); }
    /// @brief Turn motor arm to exact pulse (microseconds) within exact time frame
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    /// @param duration change position with duration in ms
    void spinPulseDuration(uint32_t pulse, uint32_t duration);
    /// @brief Turn motor arm to exact pulse (microseconds) with exact speed
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    /// @param rpm change position with speed [1:60] (RPM)
    void spinPulseRPM(uint32_t pulse, uint32_t rpm);
    /// @brief Turn motor arm to exact pulse (microseconds)
    /// @param pulse [500:2500]us. Limit: [0:period]us.
    void spinPulse(uint32_t pulse) { spinPulseDuration(pulse, 0); }
    /// @brief Set exact pulse output without any conversion and limit checking
    /// @param pulse [0:period]us
    void spinPulseRaw(uint32_t pulse);
    /// @brief Release motor from holding it's position (free spin). Turns off PWM signal. Not all motors may support this
    void coast();

    ///////////////////////
    //   Speed control
    ///////////////////////

    /// @brief Set constant Servo motor speed RPM (Rounds-Per-Minute)
    /// @param rpm Typically: [1:60]
    void setSpeedRPM(uint32_t rpm);
    /// @brief Set constant Servo motor speed sec/60deg (seconds / 60 degree)
    /// @param seconds Typically: [0.09:0.18] sec/60deg
    void setSpeedS60(float seconds);

    ///////////////////////
    // Sequence execution
    ///////////////////////

    /// @brief Run movements sequence
    /// @param seq array list of moves
    /// @param times (optional) number of times to run (0 - repeat)
    template<int SIZE>
    void run(const totem::ServoSequence (&seq)[SIZE], uint32_t times = 1) {
        run(seq, SIZE, times);
    }

    /// @brief Check if motor is moving
    /// @return [true:false] is moving 
    bool isMoving();
    /// @brief Wait till motor reaches position
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - reached position. false - timeout
    bool wait(uint32_t timeout = 0);
    /// @brief Stop motor move
    void stop();

    ///////////////////////
    //   Configuration
    ///////////////////////

    /// @brief Enable Servo peripheral
    /// @param enable [true:false] is enabled
    void setEnable(bool enable);
    /// @brief Set inverted motor spin direction
    /// @param state false - normal. true - invert
    void setInvert(bool state);
    /// @brief Set Servo signal PWM period. Default: 20000us (50Hz)
    /// @param period [1:65535] us (microseconds)
    void setPeriod(uint32_t period);
    /// @brief Set Servo signal PWM period for specific port (if hardware supports it)
    /// @param period [1:65535] us (microseconds)
    /// @param port port number
    void setPeriod(uint32_t period, uint8_t port);
    /// @brief Set Servo motor configuration. Default: 180deg, 500us, 2500us
    /// @param angleMax 180 or 270 degrees
    /// @param usMin [0:period]us pulse (500)
    /// @param usMax [0:period]us pulse (2500)
    void setMotor(uint32_t angleMax, uint32_t usMin, uint32_t usMax);
    /// @brief Trim servo motor endpoints [-100:100]%
    /// @param left amount of steer to left. Default: -100
    /// @param center center adjustment. Default: 0
    /// @param right amount of steer to right. Default: 100
    void setTrim(int left, int center, int right);
    void setTrim(int left, int right) { setTrim(left, (left+right)/2, right); }
    /// @brief Trim servo motor endpoints precisely with pulse (us)
    /// @param min [0:period]us pulse (500)
    /// @param center [0:period]us pulse (1500)
    /// @param max [0:period]us pulse (2500)
    void setTrimPulse(uint32_t min, uint32_t center, uint32_t max);
    void setTrimPulse(uint32_t min, uint32_t max) { setTrimPulse(min, (min+max)/2, max); }

    /// @brief Access Servo motor A control interface
    SingleServoClass &A;
    /// @brief Access Servo motor B control interface
    SingleServoClass &B;
    /// @brief Access Servo motor C control interface
    SingleServoClass &C;
    /// @brief Access Servo motor D control interface
    SingleServoClass &D;
    /// @brief Access specific Servo motor with array index
    /// @param num [0:3] array index
    /// @return single Servo motor control interface
    SingleServoClass& operator[](int num);

    /// @brief Read configured Servo period (us)
    /// @return [1:65535] us (microseconds)
    int getPeriod();
    /// @brief Read configured Servo period (us) of specific port (if hardware supports it)
    /// @param port port number
    int getPeriod(uint32_t port);
    /// @brief Get amount of ports board has
    /// @return [2,3,4] (depending on board revision)
    int getPortsCount();

    ServoClass();
private:
    void run(const totem::ServoSequence seq[], uint32_t size, uint32_t times);
};

} // namespace _Totem

namespace totem {

extern _Totem::ServoClass Servo;

} // namespace totem

#endif /* INCLUDE_TOTEM_SERVO */
