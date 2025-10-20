#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "motorhatlib/adafruitmotorhat.h"
#include "encoders.h"
int running = 1;

void* check_stop_running(void *arg) {
    char temp;
    scanf("%c", &temp);

    running = 0;
}

int main() {
    printf("Wall-C!\n"); 

    pthread_t stop_running_thread;
    pthread_create(&stop_running_thread, 0, check_stop_running, 0);

    if (gpioInitialise() < 0) {
        printf("Failed to init pigpio lib...\n");
        return 0;    
    }

    AdafruitMotorHAT hat;

    std::shared_ptr<AdafruitDCMotor> motor1 = hat.getMotor(1);
    std::shared_ptr<AdafruitDCMotor> motor2 = hat.getMotor(4);

    if (!motor1 | !motor2) {
        printf("Couldn't get the motors...\n");
        return 0;
    }

    motor1->setSpeed (0.5 * 255);
    motor2->setSpeed (0.5 * 255);

    // One of the motors is wired backwards
    motor1->run(AdafruitDCMotor::kForward);
    motor2->run(AdafruitDCMotor::kForward);
    sleep(2);

    // release the motor after use
    motor1->run(AdafruitDCMotor::kRelease);
    motor2->run(AdafruitDCMotor::kRelease);

    encoders_init();

// Sonar testing code
gpioSetMode(TRIG, 24); // Set TRIG pin as output
    gpioSetMode(ECHO, 23); // Set ECHO pin as input
    gpioWrite(TRIG, 0); // Ensure TRIG is low

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
// Servo Testing code 
/* const unsigned SERVO_GPIO = 23;   // change if needed
    gpioSetMode(SERVO_GPIO, PI_OUTPUT);

    // Move to a few positions with brief pauses
    int positions[] = {500,600,700,1000, 1200,1500,1700,1900,2200,2500}; // µs pulse widths
    for (int pw : positions) {
        gpioServo(SERVO_GPIO, pw);    // 500–2500 µs typical
        gpioDelay(1000 * 1000);        // 1000 ms for the servo to move
    }

    // Stop sending pulses (releases torque)
    gpioServo(SERVO_GPIO, 0);
    while (running) {
        gpioDelay(1000000); // 1 seconds
        std::cout << "Left: " << encoders_get(ENCODER_LEFT_PIN).value << "   Right: " << encoders_get(ENCODER_RIGHT_PIN).value << "\n";
    }

    gpioTerminate(); 
    
    return 0;
}
