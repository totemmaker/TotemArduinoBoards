/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_DRIVETRAIN
#define INCLUDE_TOTEM_DRIVETRAIN

#include "private/totem-dc.h"
#include "private/totem-servo.h"

namespace _Totem {

class DrivetrainClass {
public:

    /// @brief Assign motor to left wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelLeft(SingleDCClass &motor, bool invert = false);
    /// @brief Assign motor to left front wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelLeftFront(SingleDCClass &motor, bool invert = false);
    /// @brief Assign motor to left rear wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelLeftRear(SingleDCClass &motor, bool invert = false);
    /// @brief Assign motor to right wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelRight(SingleDCClass &motor, bool invert = false);
    /// @brief Assign motor to right front wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelRightFront(SingleDCClass &motor, bool invert = false);
    /// @brief Assign motor to right rear wheel
    /// @param motor DC.A DC.B DC.C DC.D
    /// @param invert [true:false] (optional) flip spin direction
    void setWheelRightRear(SingleDCClass &motor, bool invert = false);

    /// @brief Get assigned left front wheel motor interface
    /// @return DC.x object
    SingleDCClass& getWheelLeftFront();
    /// @brief Get assigned left rear wheel motor interface
    /// @return DC.x object
    SingleDCClass& getWheelLeftRear();
    /// @brief Get assigned right front wheel motor interface
    /// @return DC.x object
    SingleDCClass& getWheelRightFront();
    /// @brief Get assigned right rear wheel motor interface
    /// @return DC.x object
    SingleDCClass& getWheelRightRear();
    
    /// @brief Select Tank drivetrain logic
    void setDriveTank();
    /// @brief Select Mecanum drivetrain logic
    void setDriveMecanum();
    /// @brief Select Steer drivetrain logic
    void setDriveSteer();

    /// @brief Configure maximum robot speed
    /// @param speed [0:100]% limit
    void setMaxSpeed(uint8_t speed);
    /// @brief Read configured maximum speed
    /// @return [0:100]%
    int getMaxSpeed();

    /// @brief Stop driving with wheel braking.
    /// @param power [0:100]% braking power
    void brake(uint8_t power = 100);
    /// @brief Press brake together with gas. Slow down robot (100% - full stop) 
    /// @param power [0:100]% braking power
    void handbrake(uint8_t power = 100);
    /// @brief Put drivetrain to neutral (N) gear. Coast robot (free spin, no power)
    void coast() { brake(0); }

    /// @brief Spin wheels individually at speed [-100:100]%
    /// @param speedLF Left Front
    /// @param speedRF Right Front
    /// @param speedLR Left Rear
    /// @param speedRR Right Rear
    void spinWheels(int speedLF, int speedRF, int speedLR, int speedRR);
    /// @brief Spin left and right side wheels independently
    /// @param speedLeft [-100:100]% left wheels speed
    /// @param speedRight [-100:100]% right wheels speed
    void spinLeftRight(int speedLeft, int speedRight) { spinWheels(speedLeft, speedRight, speedLeft, speedRight); }
    /// @brief Start driving with turning speed and direction angle (for Mecanum drive)
    /// @param driveSpeed [-100:100]%. Negative - backwards.
    /// @param turnSpeed [-100:100]% speed of left or right turn
    /// @param driveAngle [0:359]deg drive direction angle (Mecanum drive)
    void driveTurnDirection(int driveSpeed, int turnSpeed, uint32_t driveAngle);
    /// @brief Start driving with direction angle (for Mecanum drive)
    /// @param driveSpeed [-100:100]% speed. Negative - backwards.
    /// @param driveAngle [0:359]deg drive direction angle (Mecanum drive)
    void driveDirection(int driveSpeed, uint32_t driveAngle) { driveTurnDirection(driveSpeed, 0, driveAngle); }
    /// @brief Start driving with turning speed
    /// @param driveSpeed [-100:100]% speed. Negative - backwards.
    /// @param turnSpeed [-100:100]% speed of left or right turn
    void driveTurn(int driveSpeed, int turnSpeed) { driveTurnDirection(driveSpeed, turnSpeed, 0); }
    /// @brief Start driving at percentage of speed
    /// @param speed [-100:100]% speed. Negative - backwards.
    void drive(int speed) { driveTurnDirection(speed, 0, 0); }
    /// @brief Turn in place left / right
    /// @param speed [-100:100]% turn in place speed and direction.
    void turn(int speed) { driveTurnDirection(0, speed, 0); }

    /// @brief Read applied braking power
    /// @return [0:100%] braking power
    int getBrake();
    /// @brief Read forward/backward drive speed
    /// @return [-100:100]%
    int getDrive();
    /// @brief Read left/right turn speed
    /// @return [-100:100]%. 0 - center
    int getTurn();
    /// @brief Read Mecanum move direction
    /// @return [0:359]deg angle
    int getDirection();
    /// @brief Check if robot is moving (power applied to wheel)
    /// @return [true:false] is moving
    bool isMoving();
};

} // namespace _Totem

extern _Totem::DrivetrainClass Drivetrain;

// Helper class to read joystick position
class Joystick {
public:
    // Joystick input range [-127:127]
    static uint8_t range;    // Default - 127
    // Joystick input exponential function to increase precision
    static uint8_t exponent; // Default - 2
    // Joystick center area
    static uint8_t deadzone; // Default - 0

    // Read trigger shoulder power [0:100]%
    static int getTrigger(uint8_t input);
    // Read axis position [-100:100]%
    static int getAxis(int axis);
    // Read joystick angle from center [0:359] degrees
    static int getAngle(int x, int y);
    // Read joystick position from center [0:100]%
    static int getMagnitude(int x, int y);

    // exp - exponential function to smooth input value
    // Read trigger shoulder power [0:100]%
    static int getTrigger(uint8_t exp, uint8_t input);
    // Read axis position [-100:100]%
    static int getAxis(uint8_t exp, int axis);
    // Read joystick angle from center [0:359] degrees
    static int getAngle(uint8_t exp, int x, int y);
    // Read joystick position from center [0:100]%
    static int getMagnitude(uint8_t exp, int x, int y);
};

#endif /* INCLUDE_TOTEM_DRIVETRAIN */
