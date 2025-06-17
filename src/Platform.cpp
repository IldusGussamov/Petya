#include "Platform.hpp"
#include <GL/freeglut.h>
#include "utils.hpp"

Platform::Platform(Point position, Velocity velocity) : Entity(position, velocity, PLATFORM_WIDTH, PLATFORM_HEIGHT)
{
    hp = 4; // начальное здоровье платформы
    updateBorders();   
}

 void Platform::draw()
 {
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