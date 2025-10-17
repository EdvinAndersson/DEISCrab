#include <pigpio.h>
#include <iostream>

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio init failed\n";
        return 1;
    }

    const unsigned SERVO_GPIO = 23;   // change if needed
    gpioSetMode(SERVO_GPIO, PI_OUTPUT);

    // Move to a few positions with brief pauses
    int positions[] = {1500, 1000, 2000, 1500}; // µs pulse widths
    for (int pw : positions) {
        std::cout << "Setting " << pw << " us\n";
        gpioServo(SERVO_GPIO, pw);    // 500–2500 µs typical
        gpioDelay(700 * 1000);        // 700 ms for the servo to move
    }

    // Stop sending pulses (releases torque)
    gpioServo(SERVO_GPIO, 0);

    gpioTerminate();
    std::cout << "Done.\n";
    return 0;
}
