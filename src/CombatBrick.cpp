// Подключение заголовка класса CombatBrick
#include "CombatBrick.hpp"
// Подключение библиотеки OpenGL для отрисовки
#include <GL/glut.h>
// Подключение заголовка ракеты (используется в логике CombatBrick)
#include "Rocket.hpp"

// Конструктор боевого кирпича: инициализация позиции, размеров и здоровья
CombatBrick::CombatBrick(Point position, Dimension width, Dimension height, Health health)
    : Brick(position, width, height, health)
{
}

// Отрисовка боевого кирпича с разной текстурой в зависимости от здоровья
void CombatBrick::draw() 
{
    // Не рисуем, если кирпич разрушен
    if (isDestroyed()) return;

    // Выбор текстуры по количеству здоровья
    switch (getHealth()) {
        case 3: DrawTexturedRectangle(COMBAT_BRICK_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(COMBAT_BRICK_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(COMBAT_BRICK_1_TEXTURE, this->position, size); break;
    }
}