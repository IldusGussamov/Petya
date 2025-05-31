#pragma once

#include "Entity.hpp"

constexpr Dimension PLATFORM_WIDTH = 0.2;
constexpr Dimension PLATFORM_HEIGHT = 0.02;

class Platform : Entity
{   
    public:
    Platform(Point position, Velocity velocity);
    void draw() override;
    private:
};
