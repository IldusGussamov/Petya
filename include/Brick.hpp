#pragma once
#include "Entity.hpp" // наследник Brick

class Brick : public Entity
{
protected:
    Health health;     // здоровье
    bool destroyed; // статус жизни
    
public:
    Brick(Point position, Dimension width, Dimension height, Health health); // конструктор

    Health getHealth() const; // получение количества здоровья

    bool isDestroyed() const; // провер

    void takeDamage(int damage); // наненесение урона

    //Определение виртуальных методов
    void update() override;
    void draw() override;
};
