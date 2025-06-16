#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Bonus : public Entity
{
public:
    Bonus(Point position, Velocity velocity, Dimension width, Dimension height);
    void draw() override;
    void update() override;
    void Collision(const Platform &platform);
    protected:
    bool isHit = false; // флаг, указывающий на то, что бонус попал в платформу
};