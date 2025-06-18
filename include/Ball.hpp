#pragma once

// Подключение необходимых заголовочных файлов
#include "Entity.hpp"    // Базовый класс Entity

#include "Platform.hpp"  // Класс Platform для обработки столкновений

#include "Brick.hpp"    // Класс Brick для обработки столкновений

// Класс Ball, представляющий игровой мяч, наследуется от Entity
class Ball : public Entity
{
public:
    // Конструктор с параметрами:
    // position - начальная позиция мяча
    // velocity - начальная скорость мяча
    // size - размеры мяча
    Ball(Point position, Velocity velocity, Dimension size);

    // Метод отрисовки мяча (переопределение виртуального метода Entity)
    void draw() override;

    // Метод обновления состояния мяча (переопределение виртуального метода Entity)
    void update() override;

    // Метод для "прилипания" мяча к платформе
    void stick();

    // Метод проверки столкновения с платформой
    // Возвращает true при столкновении
    bool Collision(const Platform &platform);

    // Метод проверки столкновения с кирпичом
    // Возвращает true при столкновении
    bool Collision(const Brick &brick);

    // Флаг, указывающий прилип ли мяч к платформе
    bool isStick;

    // Угол вращения мяча (для визуальных эффектов)
    Angle rotate = 0;

    // Геттер для состояния прилипания
    bool getStick();

    // Сеттер для состояния прилипания
    // status - новое состояние прилипания
    void setStick(bool status);
};