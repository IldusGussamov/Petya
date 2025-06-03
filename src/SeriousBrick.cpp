#include "SeriousBrick.hpp"
#include <GL/glut.h>

SeriousBrick::SeriousBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 2) // 2 HP
{
}

void SeriousBrick::draw()
{
    if (isDestroyed()) return;

    // Желтый при 2 HP, оранжевый при 1 HP
    switch (getHealth()) {
        case 2: glColor3f(1.0f, 1.0f, 0.0f); break;
        case 1: glColor3f(1.0f, 0.5f, 0.0f); break;
    }
    drawRectangle(getBorders());
}
