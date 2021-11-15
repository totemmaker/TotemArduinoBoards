#ifndef LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES
#define LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES

#include <stdint.h>
#include <stdbool.h>

namespace Feature {
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
     * @param inverted invert all channels [true:false]
     */
    void setDCInvert(bool inverted);
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
     * @param power amount of braking power [0:100]% for all channels
     */
    void setDCAutobrake(uint8_t power);
    /**
     * @brief Set DC automatic braking. Will brake motor when power is set to 0
     * 
     * @param powerA amount of channel A braking power [0:100]%
     * @param powerB amount of channel B braking power [0:100]%
     * @param powerC amount of channel C braking power [0:100]%
     * @param powerD amount of channel D braking power [0:100]%
     */
    void setDCAutobrake(uint8_t powerA, uint8_t powerB, uint8_t powerC, uint8_t powerD);
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
class DCABCD {
public:
    // Enable DC peripheral
    void enable();
    // Disable DC peripheral
    void disable();
    // Write individual power for each motor channel [-100:100]
    void power(int8_t powerA, int8_t powerB, int8_t powerC, int8_t powerD);
    // Write individual braking power of each motor channel [0:100]
    void brake(uint8_t powerA, uint8_t powerB, uint8_t powerC, uint8_t powerD);
    // Set DC port inversion [true:false]
    void setInvert(bool A, bool B, bool C, bool D);
    // Set DC automatic braking power [0:100]
    void setAutobrake(uint8_t powerA, uint8_t powerB, uint8_t powerC, uint8_t powerD);
};
// X4.dcXX
class DCXX {
protected:
    const uint32_t cmd;
public:
    DCXX(uint32_t cmd) : cmd(cmd) { }
    // Play specified freeqency
    void tone(uint16_t frequency, uint16_t duration = 0);
    // Switch individual mode
    void setModeIndividual();
    // Switch to combined mode
    void setModeCombined();
    // Set motor group PWM frequency (default 50Hz)
    void setFreq(uint32_t frequency);
    // Set motor group maximum power range (default 0-100)
    void setPowerRange(uint16_t power);
};
// X4.dcX
class DCX {
protected:
    const uint32_t cmd;
public:
    DCX(uint32_t cmd) : cmd(cmd) { }
    // Enable DC channel
    void enable();
    // Disable DC channel
    void disable();
    // Spin motor at specified power [-100:100]
    void power(int32_t power);
    // Brake motor at specified power [0:100]
    void brake(uint16_t power = 100);
    // Invert DC channel
    void setInvert(bool state);
    // Set DC channel autobraking when power is set to 0
    void setAutobrake(bool state);
    void setAutobrake(int power);
};
/*******************************
          X4.servo
*******************************/
class SERVOABC {
public:
    // Enable Servo peripheral
    void enable();
    // Disable Servo peripheral
    void disable();
    // Set Servo period [0:20000] (20ms)
    void setPeriod(uint32_t period);
    // Turn motor to specified position [-100:100] in percentage
    void pos(int8_t positionA, int8_t positionB, int8_t positionC);
    // Turn motor to specified angle [0:180] in degrees
    void angle(uint8_t angleA, uint8_t angleB, uint8_t angleC);
    // Turn motor to specified pulse [500:2500] in milliseconds
    void pulse(uint16_t pulseA, uint16_t pulseB, uint16_t pulseC);
};
// X4.servoX
class SERVOX {
protected:
    const uint32_t cmd;
public:
    SERVOX(uint32_t cmd) : cmd(cmd) { }
    // Enable Servo channel
    void enable();
    // Disable Servo channel
    void disable();
    // Turn motor to specified position [-100:100] in percentage
    void pos(int8_t position, uint16_t duration = 0);
    // Turn motor to specified angle [0:180] in degrees
    void angle(uint8_t angle, uint16_t duration = 0);
    // Turn motor to specified pulse [500:2500] in microseconds
    void pulse(uint16_t pulse, uint16_t duration = 0);
    // Get current motor position in percentage [-100:100]
    int8_t getPos();
    // Get current motor angle [0:180]
    uint8_t getAngle();
    // Get current motor position in microseconds [500:2500]
    uint16_t getPulse();

    // Invert Servo motor spin direction
    void setInvert(uint8_t state);
    // Set constant Servo motor speed RPM (Rounds-Per-Minute)
    void setSpeed(uint16_t rpm);
    // Set constant Servo motor speed RPH (Rounds-Per-Hour)
    void setSpeedRPH(uint16_t rph);
    // Set Servo low & high pulse (microseconds) limits (default 500, 2500)
    void setPulseMinMax(uint16_t min, uint16_t max);
};
/*******************************
          X4.rgb
*******************************/
class RGBABCD  {
public:
    // Enable RGB peripheral
    void enable();
    // Disable RBB peripheral
    void disable();
    // Reset to default color
    void reset();
    // Light LED with Totem color
    void colorTotem();
    // Light LED with brightness, red, green, blue [0:255]
    void color(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Light LED with red, green, blue [0:255]
    void color(uint8_t r, uint8_t g, uint8_t b);
    // Light LED with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void color(uint8_t alpha, uint32_t hex);
    // Light LED with HEX color code [0:0xFFFFFFFF] (including brightness)
    void color(uint32_t hex);
    // Turn LED on
    void on();
    // Turn LED off
    void off();
    // Toggle on / off
    void toggle();
    // Turn on or off
    void set(uint8_t state);
    // Set LED fade with Totem color
    void fadeColorTotem();
    // Set LED fade with alpha, red, green, blue [0:255]
    void fadeColor(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with red, green, blue [0:255]
    void fadeColor(uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void fadeColor(uint8_t alpha, uint32_t hex);
    // Set LED fade with HEX color code [0:0xFFFFFFFF] (including brightness)
    void fadeColor(uint32_t hex);
    // Start all LED fading
    void fadeStart(uint32_t duration);
};
// X4.rgbX
class RGBX {
protected:
    const uint32_t cmd;
public:
    RGBX(uint32_t cmd) : cmd(cmd) { }
    // Set LED with brightness, red, green, blue [0:255]
    void color(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Set LED with red, green, blue [0:255]
    void color(uint8_t r, uint8_t g, uint8_t b);
    // Set LED with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void color(uint8_t alpha, uint32_t hex);
    // Set LED with HEX color code [0:0xFFFFFFFF] (including brightness)
    void color(uint32_t hex);
    // Turn LED on
    void on();
    // Turn LED off
    void off();
    // Toggle on / off
    void toggle();
    // Turn on or off
    void set(uint8_t state);
    // Set LED fade with alpha, red, green, blue [0:255]
    void fadeColor(uint8_t alpha, uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with red, green, blue [0:255]
    void fadeColor(uint8_t r, uint8_t g, uint8_t b);
    // Set LED fade with brightness [0:255] and HEX color code [0:0xFFFFFF]
    void fadeColor(uint8_t alpha, uint32_t hex);
    // Set LED fade with HEX color code [0:0xFFFFFFFF] (including brightness)
    void fadeColor(uint32_t hex);
    // Start LED channel fading
    void fadeStart(uint32_t duration);
};
/*******************************
          X4.gpioX
*******************************/
class GPIO {
protected:
    const uint32_t cmd;
public:
    GPIO(uint32_t cmd) : cmd(cmd) { }
    // Write pin digital state [HIGH:LOW]
    void digitalWrite(uint8_t val);
    // Read pin digital state [HIGH:LOW]
    int digitalRead();
    // Write PWM output [0:20]
    void analogWrite(uint8_t val);
    // Read analog input [0:1023]
    int analogRead();
    // Set pin pullup mode [HIGH:LOW]
    void pullMode(uint8_t mode);
    // Register GPIO event
    // void addEvent(void (*gpioEvt)(void));
};
/*******************************
          X4.module
*******************************/
class ModuleScan {
public:
    // Get last received module number
    uint16_t getLastNumber();
    // Get last received module serial
    uint16_t getLastSerial();
    // Request module ping back
    void ping(uint16_t number = 0, uint16_t serial = 0);
    // Register module discovery event
    void addEvent(void (*moduleEvt)(void));
};
/*******************************
          X4.function
*******************************/
class Function {
    const uint32_t id;
public:
    Function(uint32_t id) : id(id) { }
    // Get value passed to function
    int32_t get();
    // Register function event
    void addEvent(void (*functionEvt)(void));
};
} // namespace Feature

#endif /* LIB_ROBOBOARDX4_SRC_ROBOBOARDX4FEATURES */
