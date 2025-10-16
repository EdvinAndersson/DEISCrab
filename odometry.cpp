#include "odometry.h"

const float WHEEL_RADIUS = 0.015f;       // 15 mm radius
const float WHEEL_BASE = 0.14f;        // 140 mm between wheels
const int TICKS_PER_REV = 1024 * 15 * 4 / (2.0f * M_PI * WHEEL_RADIUS);  // ticks per full wheel revolution

Pose computeOdometryDelta(
    int left_ticks, int right_ticks,
    int last_left_ticks, int last_right_ticks,
    double encoder_noise_std) // in meters
{
    // Tick differences
    int delta_left_ticks  = left_ticks - last_left_ticks;
    int delta_right_ticks = right_ticks - last_right_ticks;

    // Convert to distance
    double distance_per_tick = (2 * M_PI * WHEEL_RADIUS) / TICKS_PER_REV;
    double d_left  = delta_left_ticks  * distance_per_tick;
    double d_right = delta_right_ticks * distance_per_tick;

    // Compute delta motion in robot frame
    double d_center = (d_right + d_left) / 2.0;
    double d_theta  = (d_right - d_left) / WHEEL_BASE;

    Pose odom;

    // Pose in robot frame: x forward, y sideways (usually 0), theta rotation
    odom.pos.x = d_center;
    odom.pos.y = 0.0;
    odom.theta = d_theta;

    // Estimated uncertainty (tune or model based on system)
    odom.sigma_pos.x = std::abs(d_center * 0.05) + encoder_noise_std;  // 5% of distance
    odom.sigma_pos.y = 0.01;  // Small lateral uncertainty
    odom.sigma_theta = std::abs(d_theta * 0.1) + 0.01; // 10% of angle, min 0.01 rad

    return odom;
}