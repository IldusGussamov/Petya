#include "utils.hpp"
#include <math.h>

Velocity calculateBounceDirection(Velocity old_velocty, Normal normal)
{
    Velocity new_velocity;

    float angle = abs(acos((old_velocty.x * normal.x + old_velocty.y * normal.y) / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)) * sqrt(pow(old_velocty.x, 2) + pow(old_velocty.y, 2)))));
    angle = angle > M_PI/2 ? M_PI-angle : angle;
    angle = M_PI - 2*angle;
    float cross = normal.x * old_velocty.y - normal.y * old_velocty.x;
    angle = cross < 0 ? angle : -angle;
    new_velocity = {cos(angle)*old_velocty.x - sin(angle)*old_velocty.y, sin(angle)*old_velocty.x + cos(angle)*old_velocty.y};

    return new_velocity;
}
