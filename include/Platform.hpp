#pragma once
#include "Entity.hpp" // наследник Platform

class Platform : public Entity
{
public:
    Platform(Point position, Velocity velocity); // конструктор

    // определение виртуальных методов
    void draw() override;
    void update() override;
    void hit(); // удар по здоровью платформы
    Health getHealth();

private:
    Health hp;
};
