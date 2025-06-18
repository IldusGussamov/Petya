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
        case 3: DrawTexturedRectangle(MAGIC_BRICK_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(MAGIC_BRICK_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(MAGIC_BRICK_1_TEXTURE, this->position, size); break;
    }
}
