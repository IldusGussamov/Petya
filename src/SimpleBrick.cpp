#include "SimpleBrick.hpp"
#include <GL/glut.h>

SimpleBrick::SimpleBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 1) // 1 HP
{
}

void SimpleBrick::draw()
{
    if (isDestroyed()) return;
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    drawBorderRectangle(this->borders);
} 