#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

static const uint8_t BUTTON_BUILTIN = 18;
static const uint8_t LED_BUILTIN = 13;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t MOSI  = 14;
static const uint8_t MISO  = 23;
static const uint8_t SCK   = 25;
static const uint8_t SS    = 26;

static const uint8_t A0 = 14;
static const uint8_t A2 = 25;
static const uint8_t A3 = 26;

static const uint8_t T0 = 14;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

static const uint8_t GPIOA = 14;
static const uint8_t GPIOB = 23;
static const uint8_t GPIOC = 25;
static const uint8_t GPIOD = 26;

#endif /* Pins_Arduino_h */
