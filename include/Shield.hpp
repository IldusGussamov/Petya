#pragma once
#include "Entity.hpp"
#include "utils.hpp"

class Shield : public Entity
{
    public:
        Shield(Point position, Size platformSize);
        void draw() override;
        void update() override;
        bool isBroken();
        bool isActivated();
        void hit();
        void activate();
        void deactivate();
    private:
        bool isBreak = false;
        bool isActivate = false;
};