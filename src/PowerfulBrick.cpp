#include "PowerfulBrick.hpp"
#include <GL/glut.h>

PowerfulBrick::PowerfulBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 3) // 3 HP
{
}

void PowerfulBrick::draw()
{
    if (isDestroyed()) return;

    // плавный переход от синего к фиолетовому
    switch (getHealth()) {
        case 3: glColor3f(0.0f, 0.0f, 1.0f); break;
        case 2: glColor3f(0.5f, 0.0f, 0.8f); break;
        case 1: glColor3f(0.8f, 0.0f, 0.8f); break;
    }
    drawRectangle(getBorders());
}
