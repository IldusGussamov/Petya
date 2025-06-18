#include "PowerfulBrick.hpp"
#include <GL/glut.h>
#include "utils.hpp"

// Конструктор мощного кирпича: инициализация позиции, размеров и 3 HP
PowerfulBrick::PowerfulBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 3) // 3 HP
{
}

// Отрисовка мощного кирпича с разной текстурой в зависимости от здоровья
void PowerfulBrick::draw() 
{
    // Не рисуем, если кирпич разрушен
    if (isDestroyed()) return;

    // Плавный переход от синего к фиолетовому по количеству здоровья
    switch (getHealth()) {
        case 3: DrawTexturedRectangle(POWERFUL_BRICK_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(SERIOUS_BRICK_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size); break;
    }
}