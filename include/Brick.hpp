#pragma once

// Базовый класс для кирпичей, наследуется от Entity
#include "Entity.hpp"

class Brick : public Entity
{
protected:
    // Состояние кирпича
    Health health;       // Текущее количество здоровья

    bool destroyed;      // Флаг уничтожения (true если здоровье <= 0)

    bool havePattern;    // Наличие паттерна движения (true если кирпич двигается)
    
    // Параметры движения (актуальны если havePattern == true)
    int moveDirection;   // Направление движения: 
                         // 0 - вправо, 1 - влево, 
                         // 2 - вверх, 3 - вниз
    float moveSpeed;     // Скорость перемещения

    float moveDistance;  // Пройденное расстояние в текущем направлении
    
    float maxDistance;   // Максимальное расстояние перед сменой направления
    
public:
    // Конструктор кирпича
    // position - координаты левого верхнего угла
    // width, height - размеры кирпича
    // health - начальное количество здоровья
    Brick(Point position, Dimension width, Dimension height, Health health);

    // Возвращает текущее количество здоровья
    Health getHealth() const;

    // Проверяет, уничтожен ли кирпич
    bool isDestroyed() const;

    // Наносит урон кирпичу
    // damage - количество урона
    void takeDamage(int damage);

    // Обновляет состояние кирпича (переопределение виртуального метода Entity)
    void update() override;

    // Отрисовывает кирпич (переопределение виртуального метода Entity)
    void draw() override;

    // Устанавливает параметры движения кирпича
    // speed - скорость перемещения
    // distance - расстояние перед сменой направления
    // initialDirection - начальное направление движения
    void setMovePattern(float speed, float distance, int initialDirection);

    // Возвращает текущее направление движения
    int getCurrentPattern() const;

    // Проверяет, имеет ли кирпич паттерн движения
    // Используется классом Map для обработки движущихся кирпичей
    bool hasPattern() const;
};