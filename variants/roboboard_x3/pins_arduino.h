#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

static const uint8_t BUTTON_BUILTIN = 0;
static const uint8_t LED_BUILTIN = 40+13;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN
#define RGB_BUILTIN LED_BUILTIN
#define RGB_BRIGHTNESS 64

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 15;
static const uint8_t SCL = 5;

#define WIRE1_PIN_DEFINED 1
static const uint8_t SDA1 = 33;
static const uint8_t SCL1 = 32;

static const uint8_t MOSI  = 26;
static const uint8_t MISO  = 32;
static const uint8_t SCK   = 33;
static const uint8_t SS    = 14;

static const uint8_t A0 = 26;
static const uint8_t A1 = 32;
static const uint8_t A2 = 33;

static const uint8_t T0 = 26;
static const uint8_t T1 = 32;
static const uint8_t T2 = 33;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

static const uint8_t IO26 = 26;
static const uint8_t IO32 = 32;
static const uint8_t IO33 = 33;

static const uint8_t SIGA = 25;
static const uint8_t SIGB = 14;

#endif /* Pins_Arduino_h */
