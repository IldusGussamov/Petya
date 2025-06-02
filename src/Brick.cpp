#include "Brick.hpp"
#include <GL/glut.h>

Brick::Brick(Point position, Dimension width, Dimension height, int health)
    : Entity(position, Velocity{0, 0}, width, height), health(health), destroyed(false)
{
    updateBorders();
}

int Brick::getHealth() const
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
    if (destroyed)
        return;

    // цвета для различия прочности
    if (health >= 3)
    {
        glColor3f(1.0f, 0.0f, 0.0f); // Красный
    }
    else if (health == 2)
    {
        glColor3f(1.0f, 1.0f, 0.0f); // Желтый
    }
    else
    {
        glColor3f(0.0f, 0.0f, 1.0f); // Синий
    }

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i)
    {
        glVertex2f(borders[i].x, borders[i].y);
    }
    glEnd();
}

void Brick::updateBorders()
{
    // Низ
    borders[0] = {position.x - size.width / 2, position.y - size.height / 2};
    borders[1] = {position.x + size.width / 2, position.y - size.height / 2};
    // Вверх
    borders[2] = {position.x + size.width / 2, position.y + size.height / 2};
    borders[3] = {position.x - size.width / 2, position.y + size.height / 2};
} 
