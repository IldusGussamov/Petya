#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Bonus : public Entity
{
public:
    Bonus(Point position, Dimension width, Dimension height);
    void draw() override;
    void update() override;
    void Collision(const Platform &platform);
    int getBonusType() const; // получение типа бонуса
     bool isHit = false;
    protected:
    int bonusType = 0;
};