#include "Platform.hpp"
#include <GL/freeglut.h>
#include "utils.hpp"

Platform::Platform(Point position, Velocity velocity) : Entity(position, velocity, PLATFORM_WIDTH, PLATFORM_HEIGHT)
{
    hp = PLATFORM_HEALTH + 1; // начальное здоровье платформы
    updateBorders();   
}

 void Platform::draw()
 {
    switch (getHealth()) {
        case 3: DrawTexturedRectangle(PLATFORM_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(PLATFORM_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(PLATFORM_1_TEXTURE, this->position, size); break;
        case 0: DrawTexturedRectangle(PLATFORM_0_TEXTURE, this->position, size); break;
    }
 }
void Platform::update()
{
    position.x += velocity.x * speedMultiplier;
    position.y += velocity.y * speedMultiplier;
    updateBorders();
}

Health Platform::getHealth()
{
    return hp;
}

void Platform::hit()
{
    hp--;
    if (hp < 0)
    {
        hp = 0;
    }
}