#include "PowerfulBrick.hpp"
#include <GL/glut.h>

PowerfulBrick::PowerfulBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 3) // 3 HP
{
}

void PowerfulBrick::draw() 
{
    if (isDestroyed()) return;

    // плавный переход от фиолетового к синему
    switch (getHealth()) {
        case 3: glColor3f(0.4f, 0.3f, 0.8f); break;
        case 2: glColor3f(0.2549f, 0.1294f, 0.6039f); break;
        case 1:  glColor3f(0.0f, 0.4f, 0.8f); break;
    }
    drawBorderRectangle(this->borders);
}
