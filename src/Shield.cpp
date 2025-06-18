#include "Shield.hpp"

// Обработка удара по щиту — помечаем как сломанный
void Shield::hit()
{
    isBreak = true;
}

// Отрисовка щита с увеличенным размером
void Shield::draw()
{
    DrawTexturedRectangle(SHIELD_TEXTURE, position, {size.width * 1.6f, size.height * 3});
}

// Обновление состояния щита (деактивация при поломке и обновление границ)
void Shield::update()
{
    if (isBreak)
        isActivate = false;
    updateBorders();
}

// Проверка, сломан ли щит
bool Shield::isBroken()
{
    return isBreak;
}

// Конструктор щита: инициализация позиции и размеров по платформе
Shield::Shield(Point position, Size platformSize)
    : Entity{position, {0, 0}, platformSize.width, platformSize.height}
{
}

// Активация щита (включить и сбросить поломку)
void Shield::activate()
{
    isActivate = true;
    isBreak = false;
}

// Деактивация щита (выключить и пометить как сломанный)
void Shield::deactivate()
{
    isActivate = false;
    isBreak = true;
}

// Проверка, активирован ли щит
bool Shield::isActivated()
{
    return isActivate;
}