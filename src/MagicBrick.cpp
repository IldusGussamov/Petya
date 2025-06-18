// Подключение заголовка класса MagicBrick
#include "MagicBrick.hpp"
// Подключение библиотеки OpenGL для отрисовки
#include <GL/glut.h>
// Подключение заголовка ракеты (используется в логике MagicBrick)
#include "Rocket.hpp"

// Конструктор магического кирпича: инициализация позиции, размеров и здоровья
MagicBrick::MagicBrick(Point position, Dimension width, Dimension height, Health health)
    : Brick(position, width, height, health)
{
}

// Отрисовка магического кирпича с разной текстурой в зависимости от здоровья
void MagicBrick::draw() 
{
    // Не рисуем, если кирпич разрушен
    if (isDestroyed()) return;

    switch (getHealth()) {
        case 3: DrawTexturedRectangle(MAGIC_BRICK_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(MAGIC_BRICK_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(MAGIC_BRICK_1_TEXTURE, this->position, size); break;
    }
}