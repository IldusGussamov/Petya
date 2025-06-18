#include "SeriousBrick.hpp"
#include <GL/glut.h>

// Конструктор серьёзного кирпича: инициализация позиции, размеров и 2 HP
SeriousBrick::SeriousBrick(Point position, Dimension width, Dimension height)
    : Brick(position, width, height, 2) // 2 HP
{
}

// Отрисовка серьёзного кирпича с разной текстурой в зависимости от здоровья
void SeriousBrick::draw()
{
    // Не рисуем, если кирпич разрушен
    if (isDestroyed())
        return;

    switch (getHealth())
    {
        case 2: DrawTexturedRectangle(SERIOUS_BRICK_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(SIMPLE_BRICK_TEXTURE, this->position, size); break;
    }
}