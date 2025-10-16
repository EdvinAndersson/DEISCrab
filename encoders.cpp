#include "encoders.h"

Encoder encoder_left, encoder_right;

void encoders_init() {
    encoder_left.value = 0;
    encoder_left.pin = ENCODER_LEFT_PIN;

    encoder_right.value = 0;
    encoder_right.pin = ENCODER_RIGHT_PIN;

    gpioSetMode(encoder_left.pin, PI_INPUT);
    gpioSetPullUpDown(encoder_left.pin, PI_PUD_UP);
    gpioSetAlertFunc(encoder_left.pin, encoders_callback);

    gpioSetMode(encoder_right.pin, PI_INPUT);
    gpioSetPullUpDown(encoder_right.pin, PI_PUD_UP);
    gpioSetAlertFunc(encoder_right.pin, encoders_callback);
}

void encoders_callback(int gpio, int level, uint32_t tick) {
    if (level == 1) { // rising edge
        if (gpio == ENCODER_LEFT_PIN) encoder_left.value++;
        if (gpio == ENCODER_RIGHT_PIN) encoder_right.value++;
    }
}

Encoder encoders_get(uint32_t pin) {
    if (pin == ENCODER_LEFT_PIN) {
        return encoder_left;
    }
    if (pin == ENCODER_RIGHT_PIN) {
        return encoder_right;
    }
    Encoder e;
    return e;
}