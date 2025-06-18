#include "SimpleBrick.hpp"
#include <GL/glut.h>

SimpleBrick::SimpleBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 1) // 1 HP
{
}

void SimpleBrick::draw()
{
    if (isDestroyed()) return;
        glColor3f(0.0f, 0.4f, 0.8f);
    drawBorderRectangle(this->borders);
} 