#pragma once
#include "Brick.hpp"

class MagicBrick : public Brick
{
public:

    MagicBrick(Point position, Dimension width, Dimension height);

    void draw() override;
};