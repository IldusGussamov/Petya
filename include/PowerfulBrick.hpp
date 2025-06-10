#pragma once
#include "Brick.hpp"

class PowerfulBrick : public Brick
{
public:

    PowerfulBrick(Point position, Dimension width, Dimension height);

    void draw() override;
};