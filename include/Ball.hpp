#pragma once
#include "Entity.hpp"
#include "Platform.hpp"
#include "Brick.hpp"

class Ball : public Entity
{
public:
    Ball(Point position, Velocity velocity, Dimension size);
    void draw() override;
    void update() override;
    void Collision(const Platform &platform);
    void Collision(const Brick &brick);
};