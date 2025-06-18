#include "Entity.hpp"
#include <iostream>

Entity::Entity(Point position, Velocity velocity, Dimension width, Dimension height)
{
    this->position = position;
    this->velocity = velocity;
    size = {width, height};
    updateBorders();
}

Point Entity::getPosition() const
{
    return position;
}

Velocity Entity::getVelocity() const
{
    return velocity;
}

Size Entity::getDimensions() const
{
    return size;
}

void Entity::setVelocity(Velocity velocity)
{
    this->velocity = velocity;
}

bool Entity::checkCollision(const Entity &other)
{
    bool collisionX = (getLeftBorder() <= other.getRightBorder()) && (getRightBorder() >= other.getLeftBorder());
    bool collisionY = (getBottomBorder() <= other.getTopBorder()) && (getTopBorder() >= other.getBottomBorder());
    return collisionX && collisionY;
}

void Entity::updateBorders()
{
    borders[Sides::LEFT_TOP] = {position.x - size.width / 2, position.y + size.height / 2};
    borders[Sides::RIGHT_TOP] = {position.x + size.width / 2, position.y + size.height / 2};
    borders[Sides::RIGHT_BOTTOM] = {position.x + size.width / 2, position.y - size.height / 2};
    borders[Sides::LEFT_BOTTOM] = {position.x - size.width / 2, position.y - size.height / 2};
}

void Entity::updatePosition()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

void Entity::resetVelocity()
{
    velocity.x = 0;
    velocity.y = 0;
}

Coordinate Entity::getLeftBorder() const
{
    return borders[LEFT_TOP].x;
}

Coordinate Entity::getRightBorder() const
{
    return borders[RIGHT_TOP].x;
}

Coordinate Entity::getTopBorder() const
{
    return borders[LEFT_TOP].y;
}

Coordinate Entity::getBottomBorder() const
{
    return borders[RIGHT_BOTTOM].y;
}

void Entity::setPosition(Point position)
{
    this->position = position;
}