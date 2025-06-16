#pragma once
#include "Entity.hpp" // наследник Brick

class Brick : public Entity
{
protected:
    Health health;     // здоровье
    bool destroyed; // статус жизни
    bool actioned; // статус жизни
    
public:
    Brick(Point position, Dimension width, Dimension height, Health health); // конструктор

    Health getHealth() const; // получение количества здоровья

    bool isDestroyed() const; // провер

    bool isActioned() const; //провекрка для дропа бонуса или ракеты

    void takeDamage(int damage); // наненесение урона

    //Определение виртуальных методов
    void update() override;
    
    void draw() override;
};
