#pragma once
#include "Entity.hpp" // наследник Brick

class Brick : public Entity
{
protected:
    Health health;      // здоровье
    bool destroyed;     // статус жизни
    bool havePattern;   // Флаг наличия паттерна движения
    int moveDirection;  // текущее направление движения (0: вправо, 1: влево, 2: вверх, 3: вниз)
    float moveSpeed;    // скорость движения
    float moveDistance; // пройденное расстояние
    float maxDistance;  // максимальное расстояние для движения в одном направлении

public:
    Brick(Point position, Dimension width, Dimension height, Health health); // конструктор

    Health getHealth() const; // получение количества здоровья

    bool isDestroyed() const; // провер

    void takeDamage(int damage); // наненесение урона

    void setMovePattern(float speed, float distance, int initialDirection); // задание параметров движения
    int getCurrentPattern() const;                                          // получение направления
    bool hasPattern() const;                                                // нужен для мапы, чтобы проверять паттерн для перемещения кирпичей

    // Определение виртуальных методов
    void update() override;
    void draw() override;
};