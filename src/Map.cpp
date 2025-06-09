#include "Map.hpp"
#include "utils.hpp"
#include <GL/freeglut.h>

Map::Map(Point position, Size size) : platform(PLATFORM_POSITION, {0, 0})
{
    this->position = position;
    this->size = size;
}

void Map::draw()
{
    glColor3f(1, 1, 1);
    drawRectangle(position, size);
    platform.draw();
    for(Ball ball : balls)
    {
        ball.draw();
    }
}

void Map::update()
{
    platform.update();
    for(Ball ball: balls)
    {   if (!isThrowBall)
            ball.setVelocity(platform.getVelocity());
        //ball.checkCollision(platform); вообще говоря в ball должна быть функция collision
        ball.update();
    }
}