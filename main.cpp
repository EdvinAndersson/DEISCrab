#include <stdio.h>

#include "motorhatlib/adafruitmotorhat.h"

int main() {
    printf("Wall-C!\n");

    AdafruitMotorHAT hat;

    std::shared_ptr<AdafruitDCMotor> motor = hat.getMotor(1);

    if (!motor) {
        printf("Couldn't get the motor...\n");
        return 0;
    }

    motor->setSpeed (255);

    motor->run (AdafruitDCMotor::kForward);

    // release the motor after use
    motor->run (AdafruitDCMotor::kRelease);

    return 0;
}
