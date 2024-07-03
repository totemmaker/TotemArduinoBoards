/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_SDK
#define INCLUDE_TOTEM_SDK

#ifdef __cplusplus

#include "totem-battery.h"
#include "totem-board.h"
#include "totem-button.h"
#include "totem-can.h"
#include "totem-color.h"
#include "totem-drivetrain.h"
#include "totem-imu.h"
#include "totem-led.h"
#include "totem-dc.h"
#include "totem-servo.h"
#include "totem-rgb.h"
#include "totem-totemapp.h"

// Create secondary loop task
void addLoop(void (*loopFunc)(void));
// System preload callback
void initRoboBoard();

#ifdef ARDUINO_ROBOBOARD_X3
#define ROBOBOARD_X3 1
#define ROBOBOARD_X4 0
#endif // ARDUINO_ROBOBOARD_X3
#ifdef ARDUINO_ROBOBOARD_X4
#define ROBOBOARD_X3 0
#define ROBOBOARD_X4 1
// Legacy RoboBoard X4 (revision 1.0) GPIO control functions
// For later boards use standard Arduino functions
void X410_digitalWrite(uint8_t pin, uint8_t value);
int X410_digitalRead(uint8_t pin);
void X410_analogWrite(uint8_t pin, int value);
int X410_analogRead(uint8_t pin);
void X410_pinMode(uint8_t pin, uint8_t mode);
#endif // ARDUINO_ROBOBOARD_X4

#ifndef REQUIRE_TOTEM_PREFIX
using namespace totem;
#endif // REQUIRE_TOTEM_PREFIX

#endif // __cplusplus

#endif // INCLUDE_TOTEM_SDK
