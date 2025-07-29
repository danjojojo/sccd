#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>
#include "./globals.h"

// PINS
#define DISPLAY_BACKLIT 4
#define BUZZER_PIN 13
#define LEFT_BUTTON 2 // 2
#define RIGHT_BUTTON 12 // 12

// GPIOS
#define WAKEUP_1 GPIO_NUM_2 // 2
#define WAKEUP_2 GPIO_NUM_12 // 12

// BATTERY
#define ADC_PIN 33 // 15
#define CONV_FACTOR 1.76
#define READS 20

// FUNCTIONS
#define BUTTON_PIN_BITMASK(GPIO) (1ULL << GPIO)

// CONSTEXPRS
constexpr uint64_t BITMASK = BUTTON_PIN_BITMASK(WAKEUP_1) | BUTTON_PIN_BITMASK(WAKEUP_2);

// STOP PLATE #93
constexpr uint8_t STOP_PLATE_MAC_ADDRESS[6] = {0x30, 0xc9, 0x22, 0xd2, 0x17, 0x1c};

#endif