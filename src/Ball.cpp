#include "Ball.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>

Ball::Ball(Point position, Velocity velocity, Dimension size) : Entity(position, velocity, size, size)
{
}

void Ball::draw()
{
    glColor3f(0, 1, 0);
    drawBorderRectangle(borders);
}
void Ball::update()
{
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
    updateBorders();
}

void Ball::Collision(const Platform &platform)
{
    if(this->checkCollision(platform))
    {
        this->setVelocity(calculateBounceDirectonPlatform(this->getVelocity(), platform.getPosition().x-this->position.x));
    }
}