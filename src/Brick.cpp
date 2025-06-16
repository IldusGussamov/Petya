#include "Brick.hpp"
#include <GL/glut.h>
#include <utils.hpp>

Brick::Brick(Point position, Dimension width, Dimension height, Health health)
    : Entity(position, Velocity{0, 0}, width, height), health(health), destroyed(false)
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
