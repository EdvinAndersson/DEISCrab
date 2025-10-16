#pragma once

#include <cmath>

#define M_PI 3.141592653

typedef struct vec2 {
    float x, y;
};

struct Pose {
    vec2 pos;
    float theta;
    vec2 sigma_pos;
    float sigma_theta;
};