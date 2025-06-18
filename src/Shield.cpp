#include "Shield.hpp"

void Shield::hit()
{
    isBreak = true;
}

void Shield::draw()
{
    DrawTexturedRectangle(SHIELD_TEXTURE, position, {size.width*1.6, size.height*3});
}

void Shield::update()
{
    if (isBreak)
        isActivate = false;
    updateBorders();
}

bool Shield::isBroken()
{
    return isBreak;
}

Shield::Shield(Point position, Size platformSize) : Entity{position, {0, 0}, platformSize.width, platformSize.height}
{
}

void Shield::activate()
{
    isActivate = true;
    isBreak = false;
}

void Shield::deactivate()
{
    isActivate = false;
    isBreak = true;
}

bool Shield::isActivated()
{
    return isActivate;
}