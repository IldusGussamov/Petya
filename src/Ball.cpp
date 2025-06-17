#include "Ball.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <iostream>

Ball::Ball(Point position, Velocity velocity, Dimension size) : Entity(position, velocity, size, size)
{
}

void Ball::draw()
{  
    glColor3f(1, 1, 1); // сброс цвета
    DrawTexturedRectangle(BALL_TEXTURE, position, size);
}
void Ball::update()
{
    this->position.x += this->velocity.x * speedMultiplier;
    this->position.y += this->velocity.y * speedMultiplier;
    updateBorders();
}

bool Ball::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        this->setVelocity(calculateBounceDirectonPlatform(this->getVelocity(), platform.getPosition().x - this->position.x));
        return true;
    }
    return false;
}

bool Ball::Collision(const Brick &brick)
{
    if (this->checkCollision(brick))
    {
        Normal normal;
        Coordinate x = (position.x - brick.getPosition().x) / (brick.getDimensions().width / 2 + this->getDimensions().width / 2);
        Coordinate y = (position.y - brick.getPosition().y) / (brick.getDimensions().height / 2 + this->getDimensions().height / 2);
        if (abs(x) <= abs(y))
            normal = {0, y / abs(y)};
        else if (abs(x) >= abs(y))
            normal = {x / abs(x), 0};
        else if (abs(x) == abs(y))
            normal = {x / abs(x), y / abs(y)};
        this->setVelocity(calculateBounceDirection(this->getVelocity(), normal));
        return true;
    }
    return false;
}