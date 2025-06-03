#pragma once
#include "Brick.hpp"

class SeriousBrick : public Brick
{
public:

    SeriousBrick(Point position, Dimension width, Dimension height);

    void draw() override;
};