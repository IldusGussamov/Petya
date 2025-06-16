#include "MagicBrick.hpp"
#include <GL/glut.h>
#include "Rocket.hpp"

MagicBrick::MagicBrick(Point position, Dimension width, Dimension height, Health health)
    : Brick(position, width, height, health)
{
}

void MagicBrick::draw() 
{
    if (isDestroyed()) return;

    // плавный переход от ярко-жёлтого к тёмно-жёлтому
    switch (getHealth()) {
        case 3: glColor3f(1.0f, 1.0f, 0.0f); break;         // ярко-жёлтый
        case 2: glColor3f(0.8f, 0.8f, 0.0f); break;         // средний жёлтый
        case 1: glColor3f(0.5f, 0.5f, 0.0f); break;         // тёмно-жёлтый
    }
    drawBorderRectangle(this->borders);
}
