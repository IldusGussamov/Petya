#include "SimpleBrick.hpp"
#include <GL/glut.h>

// Конструктор простого кирпича: инициализация позиции, размеров и 1 HP
SimpleBrick::SimpleBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 1) // 1 HP
{
}

// Отрисовка простого кирпича
void SimpleBrick::draw()
{
    // Не рисуем, если кирпич разрушен
    if (isDestroyed()) return;
    DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size);
}