#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

static const unsigned TRIG = 23; // change if you wired differently
static const unsigned ECHO = 24;

bool measure_once(double& cm_out) {
    // Ensure TRIG low for 2 ms
    gpioWrite(TRIG, 0);
    gpioDelay(2000);

    // Send 10 µs pulse
    gpioTrigger(TRIG, 10, 1);

    // Wait for echo to go HIGH (with timeout)
    uint32_t start_wait = gpioTick();
    while (gpioRead(ECHO) == 0) {
        if (gpioTick() - start_wait > 250000) return false; // 250 ms timeout
    }
    uint32_t start = gpioTick();

    // Wait for echo to go LOW (with timeout)
    while (gpioRead(ECHO) == 1) {
        if (gpioTick() - start > 300000) return false; // cap at ~5 m range
    }
    uint32_t end = gpioTick();

    uint32_t us = end - start;
    // Sound speed ~343 m/s => distance (cm) = us / 58.0 (round trip)
    cm_out = us / 58.0;
    return true;
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio init failed\n";
        return 1;
    }

    gpioSetMode(TRIG, PI_OUTPUT);
    gpioSetMode(ECHO, PI_INPUT);
    gpioWrite(TRIG, 0);

    std::cout << "HC-SR04 test on TRIG=" << TRIG << " ECHO=" << ECHO << "\n";
    for (int i = 0; i < 10; ++i) {
        double cm;
        if (measure_once(cm)) {
            std::cout << "Distance: " << cm << " cm\n";
        } else {
            std::cout << "Measurement timeout\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    gpioTerminate();
    return 0;
}
