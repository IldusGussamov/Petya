#pragma once

#include "Entity.hpp" // Базовый класс Entity

#include "utils.hpp" // Вспомогательные утилиты

// Класс Shield представляет защитный щит платформы
// Наследуется от базового класса Entity
class Shield : public Entity
{
    public:
        // Конструктор щита
        // position - позиция платформы, к которой привязан щит
        // platformSize - размер платформы для корректного размещения щита
        Shield(Point position, Size platformSize);

        // Метод отрисовки щита (переопределение виртуального метода из Entity)
        void draw() override;

        // Метод обновления состояния щита (переопределение виртуального метода из Entity)
        void update() override;

        // Проверяет, разрушен ли щит
        // Возвращает true, если щит был поврежден
        bool isBroken();

        // Проверяет, активен ли щит в данный момент
        // Возвращает true, если щит активен и не разрушен
        bool isActivated();

        // Метод обработки попадания по щиту
        // Устанавливает флаг разрушения щита
        void hit();

        // Активирует щит
        void activate();

        // Деактивирует щит
        void deactivate();

    private:
        // Флаг состояния разрушения щита
        // true - щит разрушен, false - цел
        bool isBreak = false;

        // Флаг активности щита
        // true - щит активен, false - неактивен
        bool isActivate = false;
};