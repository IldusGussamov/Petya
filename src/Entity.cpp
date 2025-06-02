#include "Entity.hpp"

Entity::Entity(Point position, Velocity velocity, Dimension width, Dimension height)
{
    this->position = position;
    this->velocity = velocity;
    this->size = {width, height};

    this->updateBorders();
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

void Entity::checkCollision(const Entity &other) const
{

}

Point* Entity::getBorders()
{
    return borders;
}

void Entity::updateBorders()
{
    this->borders[Sides::LEFT_TOP] = {position.x - size.width / 2, position.y + size.height / 2};
    this->borders[Sides::RIGHT_TOP] = {position.x + size.width / 2, position.y + size.height / 2};
    this->borders[Sides::RIGHT_BOTTOM] = {position.x + size.width / 2, position.y - size.height / 2};
    this->borders[Sides::LEFT_BOTTOM] = {position.x - size.width / 2, position.y - size.height / 2};
}

void Entity::updatePosition()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

