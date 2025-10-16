#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <iostream>

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

    while (running) {
        gpioDelay(500000); // 0.5 seconds
        std::cout << "Left: " << encoders_get(ENCODER_LEFT_PIN).value << "   Right: " << encoders_get(ENCODER_RIGHT_PIN).value << "\n";
    }

    gpioTerminate();
    
    return 0;
}
