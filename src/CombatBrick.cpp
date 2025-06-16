#include "CombatBrick.hpp"
#include <GL/glut.h>
#include "Rocket.hpp"

CombatBrick::CombatBrick(Point position, Dimension width, Dimension height, Health health)
    : Brick(position, width, height, health)
{
}

void CombatBrick::draw() 
{
    if (isDestroyed()) return;

    // плавный переход от ярко-красного к тёмно-красному
    switch (getHealth()) {
        case 3: glColor3f(1.0f, 0.0f, 0.0f); break;         // ярко-красный
        case 2: glColor3f(0.7f, 0.0f, 0.0f); break;         // средний красный
        case 1: glColor3f(0.4f, 0.0f, 0.0f); break;         // тёмно-красный
    }
    drawBorderRectangle(this->borders);
}
