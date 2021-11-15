#ifndef LIB_ROBOBOARDX4_SRC_ROBOBOARDX4
#define LIB_ROBOBOARDX4_SRC_ROBOBOARDX4

#include "RoboBoardX4Features.h"

class RoboBoardX4 {
public:
    Feature::Config config;
    Feature::Button button;
    Feature::Led led;
    Feature::DCABCD dc;
    Feature::DCXX dcAB, dcCD;
    Feature::DCX dcA, dcB, dcC, dcD;
    Feature::SERVOABC servo;
    Feature::SERVOX servoA, servoB, servoC;
    Feature::RGBABCD rgb;
    Feature::RGBX rgbA, rgbB, rgbC, rgbD;
    Feature::GPIO gpioA, gpioB, gpioC, gpioD;
    Feature::ModuleScan module;
    Feature::Function functionA, functionB, functionC, functionD;
    
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
