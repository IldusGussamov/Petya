#include "Entity.hpp"

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

void Entity::checkCollision(const Entity &other) const
{

}

Point* Entity::getBorders()
{
    return borders;
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

