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
#ifndef LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES
#define LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES

#include <stdint.h>
#include <stdbool.h>
#include "Channels.h"

namespace Features04 {
/*******************************
          X4.config
*******************************/
class Config {
public:
    /**
     * @brief Set Robot Name. Will be visible during App connection
     * 
     * @param name name up to 30 characters
     */
    void setRobotName(const char *name);
    /**
     * @brief Get the Robot Name configured with setRobotName()
     * 
     * @return char* robot name string
     */
    char* getRobotName();
    /**
     * @brief Set the Robot Model name (description)
     * 
     * @param name string of any length. Will be converted to 16-bit hash value
     */
    void setRobotModel(const char *name);
    /**
     * @brief Set the Robot Model name (description)
     * 
     * @param hash 16-bit value of model description hash [0x0000:0xFFFF]
     */
    void setRobotModel(uint16_t hash);
    /**
     * @brief Get the Robot Model name (description)
     * 
     * @return uint16_t 16-bit hash of model description name [0x0000:0xFFFF]
     */
    uint16_t getRobotModel();
    /**
     * @brief Set the Robot Color. Appearance color to easier identify robot. Will set provided color
     * during RoboBoard X4 power-on and displayed during App connection.
     * 
     * @param r Red [0:255]
     * @param g Green [0:255]
     * @param b Blue [0:255]
     */
    void setRobotColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Set the Robot Color. Appearance color to easier identify robot. Will set provided color
     * during RoboBoard X4 power-on and displayed during App connection.
     * 
     * @param hex 24-bit HEX color code [0x000000:0xFFFFFF]
     */
    void setRobotColor(uint32_t hex);
    /**
     * @brief Get the Robot Color 24-bit HEX color code
     * 
     * @return uint32_t 24-bit HEX color code [0x000000:0xFFFFFF]
     */
    uint32_t getRobotColor();
    /**
     * @brief Invert DC channel output polarity
     * 
     * @param A invert channel A [true:false]
     * @param B invert channel B [true:false]
     * @param C invert channel C [true:false]
     * @param D invert channel D [true:false]
     */
    void setDCInvert(bool A, bool B, bool C, bool D);
    /**
     * @brief Get DC channels invert parameter
     * 
     * @return uint32_t encoded 32-bit value A | B | C | D
     */
    uint32_t getDCInvert();
    /**
     * @brief Set DC automatic braking. Will brake motor when power is set to 0
     * 
     * @param powerA amount of channel A braking power [0:100]%
     * @param powerB amount of channel B braking power [0:100]%
     * @param powerC amount of channel C braking power [0:100]%
     * @param powerD amount of channel D braking power [0:100]%
     */
    void setDCAutobrake(bool powerA, bool powerB, bool powerC, bool powerD);
    /**
     * @brief Set DC automatic braking. Will brake motor when power is set to 0
     * 
     * @param powerA amount of channel A braking power [0:100]%
     * @param powerB amount of channel B braking power [0:100]%
     * @param powerC amount of channel C braking power [0:100]%
     * @param powerD amount of channel D braking power [0:100]%
     */
    void setDCAutobrake(int powerA, int powerB, int powerC, int powerD);
    /**
     * @brief Get DC channels automatic brake parameter
     * 
     * @return uint32_t encoded 32-bit value A | B | C | D
     */
    uint32_t getDCAutobrake();
    /**
     * @brief Reset configuration to default
     * 
     */
    void reset();
};
/*******************************
          X4.button
*******************************/
class Button {
public:
    /**
     * @brief Check if button is pressed
     * 
     * @return true button is pressed
     * @return false button is released
     */
    bool isPressed();
    /**
     * @brief Check if button is released
     * 
     * @return true button is released
     * @return false button is pressed
     */
    bool isReleased();
    /**
     * @brief Check if button is pressed in for amount of time
     * 
     * @param ms amount of milliseconds button is pressed
     * @return true button is pressed for ms time
     * @return false button is not pressed for ms time
     */
    bool isPressedFor(uint32_t ms);
    /**
     * @brief Check if button is released for amount of time
     * 
     * @param ms amount of milliseconds button is released
     * @return true button is released for ms time
     * @return false button is not released for ms time
     */
    bool isReleasedFor(uint32_t ms);
    /**
     * @brief Check if button was pressed earlier
     * 
     * @return true was pressed
     * @return false was not pressed
     */
    bool wasPressed();
    /**
     * @brief Check if button was released earlier
     * 
     * @return true was released
     * @return false was not released
     */
    bool wasReleased();
    /**
     * @brief Check if button was hold for a certain time
     * 
     * @param ms milliseconds how long button was held
     * @return true button was held for provided time
     * @return false button was not held for provided time
     */
    bool wasPressedFor(uint32_t ms);
    /**
     * @brief Check if button was released for a certain time
     * 
     * @param ms milliseconds how long button was released
     * @return true button was released for provided time
     * @return false button was not released for provided time
     */
    bool wasReleasedFor(uint32_t ms);
    /**
     * @brief Check if button was double clicked
     * 
     * @return true button was double clicked
     * @return false button was not double clicked
     */
    bool wasDoubleClick();
    /**
     * @brief Get time of last button state change
     * 
     * @return uint32_t milliseconds in last button state change (millis())
     */
    uint32_t lastChange();
    /**
     * @brief Register an event for button state change
     * 
     * @param buttonEvt function called on event
     */
    void addEvent(void (*buttonEvt)(void));
};
/*******************************
          X4.led
*******************************/
class Led {
public:
    // Turn LED on
    void on();
    // Turn LED off
    void off();
    // Toggle LED on / off
    void toggle();
    // Write LED state [HIGH:LOW]
    void set(uint8_t state);
    // Read LED state [HIGH:LOW]
    int isOn();
    // Blink
    void blink();
    // Blink number of times
    void blinkTimes(uint32_t count, uint32_t blinkDuration = 200);
    // Blink for length of time
    void blinkFor(uint32_t durationMs, uint32_t blinkDuration = 100);
};
/*******************************
          X4.dc
*******************************/
class DC {
public:
    // Enable motor channel
    void enable(uint8_t ch);
    // Disable motor channel
    void disable(uint8_t ch);
    // Set power for motor channel [-100:100]
    void power(uint8_t ch, int32_t power);
    // Set brake for motor channel [true:false]
    void brake(uint8_t ch, bool state = true);
    // Set brake for motor channel [0:100]
    void brake(uint8_t ch, int power);
    // Set invert state for motor channel [true:false]
    void setInvert(uint8_t ch, bool state);
    // Set automatic braking for motor channel [true:false]
    void setAutobrake(uint8_t ch, bool state);
    // Set automatic braking for motor channel [0:100]%
    void setAutobrake(uint8_t ch, int power);

    // Set motors maximum power range (default 0-100)
    void setPowerRange(uint16_t power);
};
// X4.dcXX
class DCXX {
protected:
    const uint32_t cmd;
public:
    DCXX(uint32_t cmd) : cmd(cmd) { }
    // Play specified frequency
    void tone(uint16_t frequency, uint16_t duration = 0);
    // Switch motor group to individual mode
    void setModeIndividual();
    // Switch motor group to combined mode
    void setModeCombined();
    // Set motor group PWM frequency (default 50Hz)
    void setFreq(uint32_t frequency);
};
/*******************************
          X4.servo
*******************************/
class SERVO {
public:
    // Enable servo channel
    void enable(uint8_t ch);
    // Disable servo channel
    void disable(uint8_t ch);
    // Set servo position [-100:100] in percentage
    void pos(uint8_t ch, int8_t position, uint16_t duration = 0);
    // Set servo position [0:180] in angle degrees
    void angle(uint8_t ch, uint8_t angle, uint16_t duration = 0);
    // Set servo position [500:2500] in milliseconds pulse
    void pulse(uint8_t ch, uint16_t pulse, uint16_t duration = 0);
    // Get current servo position [-100:100] in percentage
    int8_t getPos(uint8_t ch);
    // Get current servo position [0:180] in angle degrees
    uint8_t getAngle(uint8_t ch);
    // Get current servo position [500:2500] in microseconds pulse
    uint16_t getPulse(uint8_t ch);
    // Invert servo spin direction [true:false]
    void setInvert(uint8_t ch, bool state);
    // Set constant servo speed RPM (Rounds-Per-Minute)
    void setSpeed(uint8_t ch, uint16_t rpm);
    // Set constant servo speed RPH (Rounds-Per-Hour)
    void setSpeedRPH(uint8_t ch, uint16_t rph);
    // Set servo low & high pulse (microseconds) limits (default 500, 2500)
    void setPulseMinMax(uint8_t ch, uint16_t min, uint16_t max);

    // Set all servo period [0:20000] (20ms)
    void setPeriod(uint32_t period);
};
/*******************************
          X4.rgb
*******************************/
class RGB {
public:
    // Turn LED on
    void on(uint8_t ch);
    // Turn LED off
    void off(uint8_t ch);
    // Toggle LED on / off
    void toggle(uint8_t ch);
    // Turn LED on or off
    void set(uint8_t ch, uint8_t state);
    // Check if LED is on
    int isOn(uint8_t ch);
    // Set LED with brightness, red, green, blue [0:255]
    void colorARGB(uint8_t ch, uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Set LED with red, green, blue [0:255]
    void colorRGB(uint8_t ch, uint8_t r, uint8_t g, uint8_t b);
    // Set LED with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void colorAHEX(uint8_t ch, uint8_t alpha, uint32_t hex);
    // Set LED with HEX color code [0:0xFFFFFF]
    void colorHEX(uint8_t ch, uint32_t hex);
    // Set LED fade with alpha, red, green, blue [0:255]
    void fadeColorARGB(uint8_t ch, uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with red, green, blue [0:255]
    void fadeColorRGB(uint8_t ch, uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void fadeColorAHEX(uint8_t ch, uint8_t alpha, uint32_t hex);
    // Set LED fade with HEX color code [0:0xFFFFFF]
    void fadeColorHEX(uint8_t ch, uint32_t hex);
    // Start LED fading
    void fadeStart(uint8_t ch, uint32_t duration);

    // Reset to default color
    void reset();
    // Light all LED with Totem color
    void colorTotem();
    // Set all LED fade with Totem color
    void fadeColorTotem();
    // Set value mask to control multiple LED
    void setBinary(uint16_t mask);
};
/*******************************
          X4.tbus
*******************************/
class TBUS {
public:
    // Get discovered TotemBUS module number
    uint16_t getNumber();
    // Get discovered TotemBUS module serial
    uint16_t getSerial();
    // Start TotembBUS module scan
    void scan(uint16_t number = 0, uint16_t serial = 0);
    // Register TotemBUS module discovery event
    void addEvent(void (*moduleEvt)(void));
};
/*******************************
          X4.qwiic
*******************************/
class Qwiic {
public:
    // Get discovered Qwiic module address
    uint8_t getAddr();
    // Scan for connected Qwiic modules
    int scan();
    // Register Qwiic module discovery event
    void addEvent(void (*moduleEvt)(void));
};
/*******************************
          X4.function
*******************************/
class Function {
public:
    // Get called event channel value
    int32_t getData();
    // Get called channel
    int8_t getCh();
    // Is called specified event channel
    bool isEvent(uint8_t ch);
    // Register function event channel
    void addEvent(uint8_t ch, void (*functionEvt)(void));
};
} // namespace Features04

#endif /* LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES */
