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
    glColor3f(0.35, 0.42, 0.49);
    drawBorderRectangle(borders);
 }
void Platform::update()
{
    position.x += velocity.x;
    position.y += velocity.y;
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