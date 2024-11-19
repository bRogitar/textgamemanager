#pragma once
#define _USE_MATH_DEFINES // M_PI 등 수학 상수 사용을 위해 필요
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct
{
    double x;
    double y;
} Pos;

inline double DEG2RAD(double deg)
{
    return deg * M_PI / 180.0;
}

inline double CALC_DIST(const Pos &pos1, const Pos &pos2)
{
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}
