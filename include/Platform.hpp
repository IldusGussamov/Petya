#pragma once

#include "Entity.hpp"  // Базовый класс Entity

#include "Shield.hpp"  // Класс Shield для защиты платформы

// Класс Platform представляет игровую платформу
// Наследует базовую функциональность от Entity и добавляет:
// - Управление здоровьем (HP)
// - Возможность активации щита
// - Специальную графику и поведение
class Platform : public Entity
{
public:
    // Создает платформу в указанной позиции
    // position - координаты центра платформы
    // velocity - начальная скорость движения
    Platform(Point position, Velocity velocity);

    // Переопределенные методы Entity
    void draw() override;    // Отрисовка платформы с учетом состояния
    
    void update() override; // Обновление позиции и состояния

    // Наносит урон платформе (уменьшает HP)
    void hit();

    // Активирует защитный щит на платформе
    void activateShield();

    // Возвращает текущее количество здоровья
    Health getHealth();

    Shield shield;  // Объект щита, обеспечивающий защиту

private:
    Health hp;  // Текущий уровень здоровья платформы
};