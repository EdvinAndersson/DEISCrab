#pragma once

#include "my_math.h"

Pose computeOdometryDelta(
    int left_ticks, int right_ticks,
    int last_left_ticks, int last_right_ticks,
    double wheel_radius,
    double wheel_base,
    double encoder_noise_std
);