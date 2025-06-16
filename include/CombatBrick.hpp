#pragma once
#include "Brick.hpp"

class CombatBrick : public Brick
{
public:
    CombatBrick(Point position, Dimension width, Dimension height, Health health = 2); // задается с хп
    void draw() override;
};