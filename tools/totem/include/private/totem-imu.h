/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_IMU
#define INCLUDE_TOTEM_IMU

namespace totem {
///////////////////////
//  Sensor reading
///////////////////////
struct IMUData {
    // Accelerometer. Measures acceleration
    float getX_G(); // X G. Gravitational force
    float getY_G(); // Y G. Gravitational force
    float getZ_G(); // Z G. Gravitational force
    float getX_mss(); // X m/s^2. Acceleration in meters per second squared
    float getY_mss(); // Y m/s^2. Acceleration in meters per second squared
    float getZ_mss(); // Z m/s^2. Acceleration in meters per second squared
    // Gyroscope. Measures rotation speed
    float getX_dps(); // X dps. Degrees per second
    float getY_dps(); // Y dps. Degrees per second
    float getZ_dps(); // Z dps. Degrees per second
    float getX_rads(); // X rad/s. Radians per second
    float getY_rads(); // Y rad/s. Radians per second
    float getZ_rads(); // Z rad/s. Radians per second
    float getX_rpm(); // X RPM. Rounds per minute
    float getY_rpm(); // Y RPM. Rounds per minute
    float getZ_rpm(); // Z RPM. Rounds per minute
    // IMU internal temperature
    float getTempC(); // Celsius
    float getTempF(); // Fahrenheit
    // Accelerometer based board orientation of X axis. [-180:180] degree
    float getOrientX();
    // Accelerometer based board orientation of Y axis. [-180:180] degree
    float getOrientY();
    // Accelerometer based roll estimation. [-180:180] degree
    float getRoll();
    // Accelerometer based pitch estimation. [-90:90] degree
    float getPitch();
private:
    float temp;
    struct {
        float x, y, z;
    } accel, gyro;
};

} // namespace totem

namespace _Totem {

class IMUClass {
public:
    /// @brief Initialize IMU sensor
    /// @param i2cNum I2C num (default 0)
    int begin(uint8_t i2cNum = 0);
    /// @brief Read latest measurements
    /// @return Measurements object "IMUData"
    totem::IMUData read();

    ///////////////////////
    //   Configuration
    ///////////////////////

    /// @brief Set accelerometer maximum range of G force
    /// @param range values: 2, 4, 8, 16. Default: 16 (G)
    void setAccelRange(uint32_t range);
    /// @brief Set gyroscope maximum range of angle speed
    /// @param range values: 250, 500, 1000, 2000. Default 2000 (dps)
    void setGyroRange(uint32_t range);
    /// @brief Get accelerometer maximum range of G force
    /// @return [250:2000] G force
    int getAccelRange();
    /// @brief Get gyroscope maximum range of angle speed
    /// @return [2:16] angle speed
    int getGyroRange();
    /// @brief Get name of IMU sensor
    /// @return string name
    const char* getName();
    /// @brief Get I2C address of IMU sensor
    /// @return I2C address
    int getI2CAddr();
    /// @brief Check if I2C address is of IMU sensor
    /// @param i2cAddr address to check
    /// @return true if match
    bool isI2CAddr(uint8_t i2cAddr);
};

} // namespace _Totem

namespace totem {

extern _Totem::IMUClass IMU;

} // namespace totem

#endif /* INCLUDE_TOTEM_IMU */
