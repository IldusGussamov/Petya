#include "SeriousBrick.hpp"
#include <GL/glut.h>

SeriousBrick::SeriousBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 2) // 2 HP
{
}

void SeriousBrick::draw()
{
    if (isDestroyed())
        return;

    // фиолетовый при 2 хп, синий при 1 хп
    switch (getHealth())
    {
    case 2:
        glColor3f(0.2549f, 0.1294f, 0.6039f);
        break;
    case 1:
        glColor3f(0.0f, 0.4f, 0.8f);
        break;
    }
    drawBorderRectangle(this->borders); // был убран getBorders() и было дано название для отрисовки по границе
}
