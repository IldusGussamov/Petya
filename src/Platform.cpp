#include "Platform.hpp"
#include <GL/freeglut.h>
#include "utils.hpp"

// Конструктор платформы: инициализация позиции, скорости, размеров и щита
Platform::Platform(Point position, Velocity velocity)
    : Entity(position, velocity, PLATFORM_WIDTH, PLATFORM_HEIGHT), shield(position, size)
{
    hp = PLATFORM_HEALTH + 1; // начальное здоровье платформы
    updateBorders();           // обновляем границы платформы
}

// Отрисовка платформы и щита (если активирован)
void Platform::draw()
{
    // Если щит активен — рисуем его
    if (shield.isActivated())
    {
        shield.draw();
    }
    // Выбор текстуры по количеству здоровья
    switch (getHealth()) {
        case 3: DrawTexturedRectangle(PLATFORM_3_TEXTURE, this->position, size); break;
        case 2: DrawTexturedRectangle(PLATFORM_2_TEXTURE, this->position, size); break;
        case 1: DrawTexturedRectangle(PLATFORM_1_TEXTURE, this->position, size); break;
        case 0: DrawTexturedRectangle(PLATFORM_0_TEXTURE, this->position, size); break;
    }
}

// Обновление позиции платформы, размеров и состояния щита
void Platform::update()
{
    position.x += velocity.x * speedMultiplier; // движение по X
    position.y += velocity.y * speedMultiplier; // движение по Y
    shield.setPosition(position);               // обновляем позицию щита
    shield.setSize(size.width, size.height);    // обновляем размер щита
    shield.update();                            // обновляем состояние щита
    updateBorders();                            // обновляем границы платформы
}

// Получить текущее здоровье платформы
Health Platform::getHealth()
{
    return hp;
}

// Нанести урон платформе (уменьшить здоровье)
void Platform::hit()
{
    hp--;
    if (hp < 0)
    {
        hp = 0;
    }
}