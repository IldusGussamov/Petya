#pragma once
#include "Entity.hpp"

class Platform : public Entity
{   
    public:
    Platform(Point position, Velocity velocity);
    void draw() override;
    private:
};
