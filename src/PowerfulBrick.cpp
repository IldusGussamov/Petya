#include "PowerfulBrick.hpp"
#include <GL/glut.h>
#include "utils.hpp"

PowerfulBrick::PowerfulBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 3) // 3 HP
{
}

void PowerfulBrick::draw() 
{
    if (isDestroyed()) return;

    // плавный переход от фиолетового к синему
    switch (getHealth()) {
        case 3: DrawTexturedRectangle(POWERFUL_BRICK_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(SERIOUS_BRICK_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size); break;
    }
}
