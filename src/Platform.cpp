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
    glColor3f(1, 1, 1);
    DrawTexturedRectangle(PLATFORM_1_TEXTURE, position, size);
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