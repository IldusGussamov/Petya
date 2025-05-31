#include "Platform.hpp"
#include <GL/freeglut.h>

enum Sides
{
    LEFT_TOP = 0,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM
};

Platform::Platform(Point position, Velocity velocity) : Entity(position, velocity, PLATFORM_WIDTH, PLATFORM_HEIGHT)
{
    this->borders[Sides::LEFT_TOP] = {position.x - width / 2, position.y + height / 2};
    this->borders[Sides::RIGHT_TOP] = {position.x + width / 2, position.y + height / 2};
    this->borders[Sides::RIGHT_BOTTOM] = {position.x + width / 2, position.y - height / 2};
    this->borders[Sides::LEFT_BOTTOM] = {position.x - width / 2, position.y - height / 2};
}
void Platform::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2f(borders[Sides::LEFT_TOP].x, borders[Sides::LEFT_TOP].y);
    glVertex2f(borders[Sides::RIGHT_TOP].x, borders[Sides::RIGHT_TOP].y);
    glVertex2f(borders[Sides::RIGHT_BOTTOM].x, borders[Sides::RIGHT_BOTTOM].y);
    glVertex2f(borders[Sides::LEFT_BOTTOM].x, borders[Sides::LEFT_BOTTOM].y);
    glEnd();
    glPopMatrix();
}