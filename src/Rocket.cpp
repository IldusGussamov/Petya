#include "Rocket.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <cmath>

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
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist > 1.0f)
        {
            velocity.x = dx / dist * speed;
            velocity.y = dy / dist * speed;
            position.x += velocity.x;
            position.y += velocity.y;
        }
        else
        {
            launchStraight();
        }
    }
    else
    {
        // Летит по прямой
        position.x += velocity.x;
        position.y += velocity.y;
    }
    updateBorders();
}

void Rocket::draw()
{
    glColor3f(1, 0.2, 0.2);
    drawBorderRectangle(borders);
}