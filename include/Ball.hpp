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
    void stick();
    bool Collision(const Platform &platform);
    bool Collision(const Brick &brick);
    bool isStick;
    bool getStick();
    void setStick(bool status);
};