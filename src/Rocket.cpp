#include "Rocket.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <cmath>
#include "utils.hpp"
Rocket::Rocket(Point position, Dimension width, Dimension height)
    : Entity(position, ROCKET_SPEED, width, height), targeting(true) {
        boomStatus = false;
    }

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
        if (position.y >= MAP_POSITION.y - MAP_SIZE.height + PLATFORM_ZONE)
        {
            velocity.x = getNorm(ROCKET_SPEED.x, ROCKET_SPEED.y) * dx/dist;
            velocity.y = getNorm(ROCKET_SPEED.x, ROCKET_SPEED.y) * dy/dist;
        }
        else
        {
            launchStraight();
        }
    }
    updatePosition();
    updateBorders();
}

void Rocket::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        const_cast<Platform&>(platform).hit(); //снятие константности для нанесения урона платформе
        isHit = true; // флаг указывающий на попадание ракеты в платформу
    }
}

void Rocket::draw()
{
    glColor3f(1, 0.2, 0.2);
    drawBorderRectangle(borders);
}

bool Rocket::isBoom()
{
    return boomStatus;
}
void Rocket::Boom()
{
    boomStatus = true;
}