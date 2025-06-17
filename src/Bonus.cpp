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
        bonusType = dist(gen) % 9; // случайный тип бонуса
        
}

void Bonus::draw() 
{
        switch (getBonusType()) {
        case 0: DrawTexturedRectangle(BONUS_ZERO_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(BONUS_SPEED_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(BONUS_LARGE_TEXTURE, this->position, size); break;
        case 3: DrawTexturedRectangle(BONUS_SMALL_TEXTURE, this->position, size); break;
        case 4: DrawTexturedRectangle(BONUS_BALL_SPEED_TEXTURE, this->position, size); break;
        case 5: DrawTexturedRectangle(BONUS_X2_TEXTURE, this->position, size); break;
        case 6: DrawTexturedRectangle(BONUS_SWAP_TEXTURE, this->position, size); break;
        case 7: DrawTexturedRectangle(BONUS_MAGNET_TEXTURE, this->position, size); break;
        case 8: DrawTexturedRectangle(BONUS_X2_TEXTURE, this->position, size); break;
        case 9: DrawTexturedRectangle(BONUS_SHIELD_TEXTURE, this->position, size); break;
    }
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