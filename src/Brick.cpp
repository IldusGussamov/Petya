#include "Brick.hpp"

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

void Brick::update()
{
    if (health <= 0)
    {
        destroyed = true;
        return;
    }

    if (havePattern)
    {
        // Обновляем позицию
        updatePosition();
        moveDistance += moveSpeed;
        updateBorders();

        // Прошел ли отведенное состояние
        if (moveDistance >= maxDistance)
        {
            // Смена направления
            switch (moveDirection)
            {
            case 0:
                moveDirection = 1;
                setVelocity({-moveSpeed, 0});
                break; // вправо -> влево
            case 1:
                moveDirection = 0;
                setVelocity({moveSpeed, 0});
                break; // влево -> вправо
            case 2:
                moveDirection = 3;
                setVelocity({0, -moveSpeed});
                break; // вверх -> вниз
            case 3:
                moveDirection = 2;
                setVelocity({0, moveSpeed});
                break; // вниз -> вверх
            }
            moveDistance = 0; // сброс счетчика движения
        }
    }
}
void Brick::draw()
{
}