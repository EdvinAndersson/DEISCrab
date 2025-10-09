#include <stdio.h>

#include<unistd.h>

#include "motorhatlib/adafruitmotorhat.h"

int main() {
    printf("Wall-C!\n");

    AdafruitMotorHAT hat;

    std::shared_ptr<AdafruitDCMotor> motor1 = hat.getMotor(1);
    std::shared_ptr<AdafruitDCMotor> motor2 = hat.getMotor(4);

    if (!motor1 | !motor2) {
        printf("Couldn't get the motors...\n");
        return 0;
    }

    motor1->setSpeed (0.1 * 255);
    motor2->setSpeed (0.1 * 255);
// One of the motors is wired backwards
    motor1->run(AdafruitDCMotor::kForward);
    motor2->run(AdafruitDCMotor::kForward);
    sleep(2);

    // release the motor after use
    motor1->run(AdafruitDCMotor::kRelease);
    motor2->run(AdafruitDCMotor::kRelease);

    return 0;
}
