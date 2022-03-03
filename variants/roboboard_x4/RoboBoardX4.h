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
    Features04::Config config;
    Features04::Button button;
    Features04::Led led;
    Features04::DC dc;
    Features04::DCXX dcAB, dcCD;
    Features04::SERVO servo;
    Features04::RGB rgb;
    Features04::TBUS tbus;
    Features04::Qwiic qwiic;
    Features04::Function function;
    
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
    // Restart processor
    void restart();

    // Get X4 serial number
    int getSerial();
    // Get X4 board revision version number
    int getRevisionNum();
    // Get X4 driver version number
    int getDriverVersionNum();
    // Get X4 firmware version number
    int getFirmwareVersionNum();
    // Get X4 board revision version string
    char* getRevision();
    // Get X4 driver version string
    char* getDriverVersion();
    // Get X4 firmware version string
    char* getFirmwareVersion();
};

extern RoboBoardX4 X4;

#endif /* LIB_ROBOBOARDX4_SRC_ROBOBOARDX4 */
