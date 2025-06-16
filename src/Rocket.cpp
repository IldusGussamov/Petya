#include "Rocket.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <cmath>
#include "utils.hpp"

Rocket::Rocket(Point position, Velocity velocity, Dimension width, Dimension height)
    : Entity(position, velocity, width, height), targeting(true) {}

void Rocket::setTarget(const Platform &platform)
{
    targetPosition = platform.getPosition();
    targeting = true;
}

void Rocket::launchStraight()
{
    targeting = false;
}

void Rocket::update()
{
    if (targeting)
    {
        // Движение к платформе
        float dx = targetPosition.x - position.x;
        float dy = targetPosition.y - position.y;
        float dist = getNorm(dx,dy);
        if (dist > 0.5f)
        {
            velocity.x = getNorm(velocity.x, velocity.y) * dx/dist;
            velocity.y = getNorm(velocity.x, velocity.y) * dy/dist;
        }
        else
        {
            launchStraight();
        }
    }
    updatePosition();
    updateBorders();
}

void Rocket::draw()
{
    glColor3f(1, 0.2, 0.2);
    drawBorderRectangle(borders);
}