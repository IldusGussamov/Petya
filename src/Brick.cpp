#include "Brick.hpp"

Brick::Brick(Point position, Dimension width, Dimension height, Health health)
    : Entity(position, {0, 0}, width, height), 
      health(health), destroyed(false),
      havePattern(false), currentPattern(0)
{
    // базовый паттерн задаем
    movePattern[0] = movePattern[1] = movePattern[2] = movePattern[3] = 0;
    updateBorders();
}

Health Brick::getHealth() const {
    return health;
}

bool Brick::isDestroyed() const {
    return destroyed;
}

void Brick::takeDamage(int damage) {
        if (!destroyed)
    {
        health -= damage;
        if (health <= 0)
        {
            health = 0;
            destroyed = true;
        }
    }
}

void Brick::setMovePattern(int left, int right, int up, int down) {
    // max() чтобы не было отрицательных значений
    movePattern[0] = std::max(0, left);
    movePattern[1] = std::max(0, right);
    movePattern[2] = std::max(0, up);
    movePattern[3] = std::max(0, down);
    havePattern = (left > 0 || right > 0 || up > 0 || down > 0);
}

const int* Brick::getMovePattern() const {
    return movePattern;
}

int Brick::getCurrentPattern() const {
    return currentPattern;
}

void Brick::setCurrentPattern(int pattern) {
    if (pattern >= 0 && pattern < 4) {
        currentPattern = pattern;
    }
}

void Brick::decrementPattern(int direction) {
    if (direction >= 0 && direction < 4) {
        movePattern[direction] = std::max(0, movePattern[direction] - 1);
    }
}

bool Brick::hasPattern() const {
    return havePattern;
}

void Brick::update() {
    if (health <= 0) {
        destroyed = true;
    }
}

void Brick::draw() {

}