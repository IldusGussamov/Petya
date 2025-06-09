#pragma once
#include "utils.hpp"
#include "Platform.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include <vector>

class Map
{
private:
    Point position;
    Size size;
    Platform platform;
    std::vector<Ball> balls;
    std::vector<Brick> bricks;
    bool isThrowBall = false;

public:
    Map(Point position, Size size);
    void draw();
    void update();

    Coordinate leftBorder();
    Coordinate rightBorder();
    Coordinate topBorder();
    Coordinate buttomBorder();

    Point getPosition();
    Size getSize();
};