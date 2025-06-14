#pragma once
#include "Entity.hpp" // наследник Brick

class Brick : public Entity
{
protected:
    Health health;      // здоровье
    bool destroyed;     // статус жизни
    bool havePattern;   // Флаг наличия паттерна движения
    int movePattern[4]; // Массив паттернов движения [влево, вправо, вверх, вниз]
    int currentPattern; // Текущий шаг паттерна

public:
    Brick(Point position, Dimension width, Dimension height, Health health); // конструктор

    Health getHealth() const; // получение количества здоровья

    bool isDestroyed() const; // провер

    void takeDamage(int damage); // наненесение урона

    void setMovePattern(int left, int right, int up, int down);// задавание паттерна
    const int* getMovePattern() const;//получение массива паттерна
    int getCurrentPattern() const;//получение направления 
    void setCurrentPattern(int pattern);// меняет направление
    void decrementPattern(int direction);//изменение счетчика паттерна 
    bool hasPattern() const;// нужен для мапы, чтобы проверять паттерн для перемещения кирпичей

    // Эти функции скорее всего нужно вынести в мапу
    // bool canMove(int direction, const std::vector<Brick*>& bricks) const;
    // void moveByPattern(const std::vector<Brick*>& bricks);

    // Определение виртуальных методов
    void update() override;
    void draw() override;
};
