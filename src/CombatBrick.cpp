#include "CombatBrick.hpp"
#include <GL/glut.h>
#include "Rocket.hpp"

CombatBrick::CombatBrick(Point position, Dimension width, Dimension height, Type type)
    : Brick(position, width, height, type == Simple ? 1 : (type == Serious ? 2 : 3)), type(type)
{
}

void CombatBrick::draw()
{
    if (isDestroyed())
    {

        return;
    }
    glColor3f(1.0f, 0.0f, 0.0f); // Всегда красный
    drawBorderRectangle(this->borders);
}

CombatBrick::Type CombatBrick::getType() const
{
    return type;
}