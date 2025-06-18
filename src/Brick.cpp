#include "Brick.hpp"
#include <GL/glut.h>
#include <utils.hpp>

// Конструктор кирпича: инициализация позиции, размеров, здоровья и параметров движения
Brick::Brick(Point position, Dimension width, Dimension height, Health health)
    : Entity(position, {0, 0}, width, height),
      health(health), destroyed(false),
      havePattern(false), moveDirection(0),
      moveSpeed(0), moveDistance(0), maxDistance(0)
{
    updateBorders(); // обновляем границы кирпича
}

// Получить текущее здоровье кирпича
Health Brick::getHealth() const
{
    return health;
}

// Проверить, разрушен ли кирпич
bool Brick::isDestroyed() const
{
    return destroyed;
}

// Нанести урон кирпичу
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

// Обновить состояние кирпича (разрушение, движение, границы)
void Brick::update()
{
    if (health <= 0)
    {
        destroyed = true;
    }
    updateBorders();   // обновляем границы
    updatePosition();  // двигаем кирпич, если задан паттерн движения
}

// Задать параметры движения кирпича (скорость, дистанция, направление)
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
            setVelocity({moveSpeed, 0});   // вправо
            break;
        case 1:
            setVelocity({-moveSpeed, 0});  // влево
            break;
        case 2:
            setVelocity({0, moveSpeed});   // вверх
            break;
        case 3:
            setVelocity({0, -moveSpeed});  // вниз
            break;
        }
    }
}

// Проверить, есть ли у кирпича паттерн движения
bool Brick::hasPattern() const
{
    return havePattern;
}

// Получить текущее направление движения кирпича
int Brick::getCurrentPattern() const
{
    return moveDirection;
}

// Отрисовка плитки
void Brick::draw()
{
    // реализуется в наследниках
}