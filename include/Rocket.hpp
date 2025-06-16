#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Rocket : public Entity
{
public:
    Rocket(Point position, Velocity velocity, Dimension width, Dimension height);
    void setTarget(const Platform &platform);
    void launchStraight();
    void update() override;
    void draw() override;

private:
    bool targeting;
    Point targetPosition;
};
