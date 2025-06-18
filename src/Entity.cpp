// Реализация класса Entity

#include "Entity.hpp"

// Конструктор сущности: инициализация позиции, скорости и размеров
Entity::Entity(Point position, Velocity velocity, Dimension width, Dimension height)
{
    this->position = position;
    this->velocity = velocity;
    size = {width, height};
    updateBorders(); // Обновляем границы сущности
}

// Получить позицию сущности
Point Entity::getPosition() const
{
    return position;
}

// Получить скорость сущности
Velocity Entity::getVelocity() const
{
    return velocity;
}

// Получить размеры сущности
Size Entity::getDimensions() const
{
    return size;
}

// Установить скорость сущности
void Entity::setVelocity(Velocity velocity)
{
    this->velocity = velocity;
}

// Проверка столкновения с другой сущностью
bool Entity::checkCollision(const Entity &other)
{
    bool collisionX = (getLeftBorder() <= other.getRightBorder()) && (getRightBorder() >= other.getLeftBorder());
    bool collisionY = (getBottomBorder() <= other.getTopBorder()) && (getTopBorder() >= other.getBottomBorder());
    return collisionX && collisionY;
}

// Обновить координаты границ сущности
void Entity::updateBorders()
{
    borders[Sides::LEFT_TOP] = {position.x - size.width / 2, position.y + size.height / 2};
    borders[Sides::RIGHT_TOP] = {position.x + size.width / 2, position.y + size.height / 2};
    borders[Sides::RIGHT_BOTTOM] = {position.x + size.width / 2, position.y - size.height / 2};
    borders[Sides::LEFT_BOTTOM] = {position.x - size.width / 2, position.y - size.height / 2};
}

// Обновить позицию сущности с учетом скорости и множителя скорости
void Entity::updatePosition()
{
    position.x += velocity.x * speedMultiplier;
    position.y += velocity.y * speedMultiplier;
}

// Сбросить скорость сущности к нулю
void Entity::resetVelocity()
{
    velocity.x = 0;
    velocity.y = 0;
}

// Получить координату левой границы
Coordinate Entity::getLeftBorder() const
{
    return borders[LEFT_TOP].x;
}

// Получить координату правой границы
Coordinate Entity::getRightBorder() const
{
    return borders[RIGHT_TOP].x;
}

// Получить координату верхней границы
Coordinate Entity::getTopBorder() const
{
    return borders[LEFT_TOP].y;
}

// Получить координату нижней границы
Coordinate Entity::getBottomBorder() const
{
    return borders[RIGHT_BOTTOM].y;
}

// Установить позицию сущности
void Entity::setPosition(Point position)
{
    this->position = position;
}

// Установить размеры сущности и обновить границы
void Entity::setSize(Dimension width, Dimension height)
{
    size.width = width;
    size.height = height;
    updateBorders();
}

// Установить множитель скорости
void Entity::setMultiplyVelocity(float multiplier)
{
    this->speedMultiplier = multiplier;
}

// Получить множитель скорости
float Entity::getSpeedMultiplier() const
{
    return speedMultiplier;
}