#pragma once
#include "Entity.hpp" // наследник Platform
#include "Shield.hpp"

class Platform : public Entity
{
public:
    Platform(Point position, Velocity velocity); // конструктор

    // определение виртуальных методов
    void draw() override;
    void update() override;
    void hit(); // удар по здоровью платформы
    void activateShield();
    Health getHealth();

    Shield shield;
private:
    Health hp;
};
