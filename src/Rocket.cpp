#include "Rocket.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <cmath>
#include "utils.hpp"
Rocket::Rocket(Point position, Dimension width, Dimension height)
    : Entity(position, ROCKET_SPEED, width, height), targeting(false) {
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
    if (targeting and !shieldBounce)
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
    Dimension normv = getNorm(velocity.x ,velocity.y);
    Coordinate cosv = velocity.x / normv;
    Coordinate sinv = velocity.y / normv;
    glPushMatrix();
    DrawTexturedRectangle(ROCKET_TEXTURE, this->position, size, 180/M_PI*getAngle(cosv, sinv)-90);
    glPopMatrix();
}

bool Rocket::isBoom()
{
    return boomStatus;
}
void Rocket::Boom()
{
    boomStatus = true;
}

void Rocket::Collision(const Shield &shield)
{
        Normal normal;
        Coordinate x = (position.x - shield.getPosition().x) / (shield.getDimensions().width / 2 + this->getDimensions().width / 2);
        Coordinate y = (position.y - shield.getPosition().y) / (shield.getDimensions().height / 2 + this->getDimensions().height / 2);
        if (abs(x) <= abs(y))
            normal = {0, y / abs(y)};
        else if (abs(x) >= abs(y))
            normal = {x / abs(x), 0};
        else if (abs(x) == abs(y))
            normal = {x / abs(x), y / abs(y)};
        this->setVelocity(calculateBounceDirection(this->getVelocity(), normal));
}

void Rocket::Bounce()
{
    shieldBounce = true;
}