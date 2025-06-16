#include "Bonus.hpp"
#include <GL/glut.h>
#include "Platform.hpp"

Bonus::Bonus(Point position, Velocity velocity, Dimension width, Dimension height)
    : Entity(position, velocity, width, height)
{
}

void Bonus::draw() 
{
        glColor3f(0.31f, 0.78f, 0.47f);         // зеленый

    drawBorderRectangle(this->borders);
}


void Bonus::update()
{
    this->position.y += this->velocity.y;
    updateBorders();
}

void Bonus::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        isHit = true; // флаг указывающий на попадание бонуса в платформу
    }
}