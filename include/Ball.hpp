#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Ball : public Entity
{
public:
    Ball(Point position, Velocity velocity, Dimension size);
    void draw() override;
    void update() override;
    void Collision(const Platform &platform);
};