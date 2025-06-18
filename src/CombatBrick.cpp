#include "CombatBrick.hpp"
#include <GL/glut.h>
#include "Rocket.hpp"

CombatBrick::CombatBrick(Point position, Dimension width, Dimension height, Health health)
    : Brick(position, width, height, health)
{
}

void CombatBrick::draw() 
{
    if (isDestroyed()) return;

    switch (getHealth()) {
        case 3: DrawTexturedRectangle(COMBAT_BRICK_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(COMBAT_BRICK_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(COMBAT_BRICK_1_TEXTURE, this->position, size); break;
    }
}
