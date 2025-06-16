#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Bonus : public Entity
{
public:
    Bonus(Point position, Velocity velocity);
    void draw() override;
    void update() override;
    void Collision(const Platform &platform);
};