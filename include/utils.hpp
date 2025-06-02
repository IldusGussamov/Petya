#pragma once

enum Sides
{
    LEFT_TOP = 0,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM
};

using Coordinate = float;
using Dimension = float;

struct Size
{
    Dimension width;
    Dimension height;
};

struct Point 
{
    Coordinate x, y;
};

struct Normal
{
    Coordinate x, y;
};

struct Velocity
{
    Coordinate x, y;
  
};

constexpr Dimension PLATFORM_WIDTH = 0.2;
constexpr Dimension PLATFORM_HEIGHT = 0.02;

Velocity calculateBounceDirection(Velocity old_velocty, Normal normal);