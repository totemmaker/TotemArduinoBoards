#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 4
#define NUM_DIGITAL_PINS        4
#define NUM_ANALOG_INPUTS       3

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t LED_BUILTIN = 13;

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t A0 = 14;
static const uint8_t A2 = 25;
static const uint8_t A3 = 26;

static const uint8_t T0 = 14;

static const uint8_t DAC2 = 25;
static const uint8_t DAC3 = 26;

#endif /* Pins_Arduino_h */
