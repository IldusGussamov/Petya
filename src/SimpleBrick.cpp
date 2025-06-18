#include "SimpleBrick.hpp"
#include <GL/glut.h>

SimpleBrick::SimpleBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 1) // 1 HP
{
}

void SimpleBrick::draw()
{
    if (isDestroyed()) return;
        DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size);
} 