#pragma once

#include <stdint.h>

#include <pigpio.h>

#define ENCODER_LEFT_PIN 17
#define ENCODER_RIGHT_PIN 27

struct Encoder {
    uint32_t pin;
    volatile int32_t value;
};

void encoders_init();
void encoders_callback(int gpio, int level, uint32_t tick);
Encoder encoders_get(uint32_t pin);