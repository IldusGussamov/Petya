#include "Entity.hpp"

Entity::Entity(Point position, Velocity velocity, Dimension width, Dimension height)
{
    this->position = position;
    this->velocity = velocity;
    this->size = {width, height};
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

