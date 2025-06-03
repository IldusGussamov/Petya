#pragma once
#include "Brick.hpp"

class SimpleBrick : public Brick
{
public:

    SimpleBrick(Point position, Dimension width, Dimension height);

    void draw() override; // Отрисовка с уникальным цветом
};