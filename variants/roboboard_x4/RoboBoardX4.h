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
#ifndef LIB_ROBOBOARDX4_SRC_ROBOBOARDX4
#define LIB_ROBOBOARDX4_SRC_ROBOBOARDX4

#include "RoboBoardX4Features.h"

class RoboBoardX4 {
public:
    Feature::Config config;
    Feature::Button button;
    Feature::Led led;
    Feature::DC dc;
    Feature::DCXX dcAB, dcCD;
    Feature::SERVO servo;
    Feature::RGB rgb;
    Feature::GPIO gpioA, gpioB, gpioC, gpioD;
    Feature::ModuleScan module;
    Feature::Function function;
    
    RoboBoardX4();
    // Read battery voltage [8.40:12.60]
    float getBatteryVoltage();
    // Get battery charging time
    int getBatteryChargingTime();
    // Is battery charging
    bool isBatteryCharging();
    // Check if battery voltage is low (requires charging)
    bool isBatteryLow();
    // Is DC adapter connected
    bool isDC();
    // Is USB cable connected
    bool isUSB();
    // Start Bluetooth control from App service (more code size)
    bool enableAppControl();

    void reset();
    void restart();

    int getSerial();
    char* getRevision();
    char* getDriverVersion();
    char* getSoftwareVersion();
};

extern RoboBoardX4 X4;

#endif /* LIB_ROBOBOARDX4_SRC_ROBOBOARDX4 */
