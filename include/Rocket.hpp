#pragma once
#include "Entity.hpp"
#include "Platform.hpp"

class Rocket : public Entity
{
public:
    Rocket(Point position, Dimension width, Dimension height);
    void setTarget(const Platform &platform);
    void launchStraight();
    void update() override;
    void draw() override;
    bool isBoom();
    void Boom();

    void Collision(const Platform &platform);

private:
    bool targeting;
    Point targetPosition;

    bool boomStatus;

protected:
    bool isHit = false; // флаг, указывающий на то, что ракета попала в платформу
};
