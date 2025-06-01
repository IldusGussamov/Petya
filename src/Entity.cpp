#include "Entity.hpp"

Entity::Entity(Point position, Velocity velocity, Dimension width, Dimension height)
{
    this->position = position;
    this->velocity = velocity;
    this->size = {width, height};

    this->borders[Sides::LEFT_TOP] = {position.x - size.width / 2, position.y + size.height / 2};
    this->borders[Sides::RIGHT_TOP] = {position.x + size.width / 2, position.y + size.height / 2};
    this->borders[Sides::RIGHT_BOTTOM] = {position.x + size.width / 2, position.y - size.height / 2};
    this->borders[Sides::LEFT_BOTTOM] = {position.x - size.width / 2, position.y - size.height / 2};
}

Point Entity::getPosition() const
{
    return this->position;
}

Velocity Entity::getVelocity() const
{
    return this->velocity;
}

Size Entity::getDimensions() const
{
    return size;
}

void Entity::setVelocity(Velocity velocity)
{
    this->velocity = velocity;
}

