#pragma once
#include "Brick.hpp"

class CombatBrick : public Brick
{
public:
    enum Type { Simple, Serious, Powerful };
    CombatBrick(Point position, Dimension width, Dimension height, Type type);
    void draw() override;
    Type getType() const;
private:
    Type type;
};