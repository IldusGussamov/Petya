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
        case 2: DrawTexturedRectangle(SERIOUS_BRICK_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size); break;
    }
}
