#pragma once
#include "Brick.hpp"

class MagicBrick : public Brick
{
public:
    MagicBrick(Point position, Dimension width, Dimension height, Health health = 2); // задается с хп
    void draw() override;
};