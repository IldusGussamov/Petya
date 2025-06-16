#include "Bonus.hpp"
#include <GL/glut.h>
#include "Platform.hpp"
#include <random>

Bonus::Bonus(Point position, Dimension width, Dimension height)
    : Entity(position, {0,-DROP_SPEED}, width, height)
{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 100);
        bonusType = dist(gen) % 8; // случайный тип бонуса
}

void Bonus::draw() 
{
        glColor3f(0.31f, 0.78f, 0.47f);         // зеленый

    drawBorderRectangle(this->borders);
}


void Bonus::update()
{
    this->position.y += this->velocity.y;
    updateBorders();
}

void Bonus::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        isHit = true; // флаг указывающий на попадание бонуса в платформу
    }
}

int Bonus::getBonusType() const
{
    return bonusType; // возвращает тип бонуса
}