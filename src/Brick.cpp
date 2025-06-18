#include "Brick.hpp"
#include <GL/glut.h>
#include <utils.hpp>

Brick::Brick(Point position, Dimension width, Dimension height, Health health)
    : Entity(position, {0, 0}, width, height),
      health(health), destroyed(false),
      havePattern(false), moveDirection(0),
      moveSpeed(0), moveDistance(0), maxDistance(0)
{
    updateBorders();
}

Health Brick::getHealth() const
{
    return health;
}

bool Brick::isDestroyed() const
{
    return destroyed;
}

void Brick::takeDamage(int damage)
{
    if (!destroyed)
    {
        health -= damage;
        if (health <= 0)
        {
            health = 0;
            destroyed = true;
        }
    }
}

void Brick::update()
{
    if (health <= 0)
    {
        destroyed = true;
    }
    updateBorders();
    updatePosition();
}

void Brick::draw()
{
    // if (destroyed)
    //     return;

    // // цвета для различия прочности
    // if (health >= 3)
    // {
    //     glColor3f(1.0f, 0.0f, 0.0f); // красный
    // }
    // else if (health == 2)
    // {
    //     glColor3f(1.0f, 1.0f, 0.0f); // жёлтый
    // }
    // else
    // {
    //     glColor3f(0.0f, 0.0f, 1.0f); // синий
    // }

    // drawBorderRectangle(borders);
}

void Brick::setMovePattern(float speed, float distance, int initialDirection)
{
    havePattern = (speed > 0 && distance > 0);
    if (havePattern)
    {
        moveSpeed = speed;
        maxDistance = distance;
        moveDirection = initialDirection;
        moveDistance = 0;

        // Устанавливаем начальную скорость в зависимости от направления
        switch (moveDirection)
        {
        case 0:
            setVelocity({moveSpeed, 0});
            break; // вправо
        case 1:
            setVelocity({-moveSpeed, 0});
            break; // влево
        case 2:
            setVelocity({0, moveSpeed});
            break; // вверх
        case 3:
            setVelocity({0, -moveSpeed});
            break; // вниз
        }
    }
}

bool Brick::hasPattern() const
{
    return havePattern;
}

int Brick::getCurrentPattern() const
{
    return moveDirection;
}
