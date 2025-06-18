#pragma once

// Базовый класс для всех игровых объектов
#include "utils.hpp" // Вспомогательные типы (Point, Velocity и др.), функции и константы

class Entity 
{
public:
    // Основной конструктор сущности
    // position - начальная позиция центра объекта
    // velocity - начальный вектор скорости
    // width, height - размеры объекта
    Entity(Point position, Velocity velocity, Dimension width, Dimension height);

    // Чисто виртуальные методы (должны быть реализованы в производных классах)
    virtual void draw() = 0;    // Отрисовка объекта (зависит от конкретной сущности)
    
    virtual void update() = 0;  // Логика обновления состояния объекта

    // Управление состоянием объекта
    void setVelocity(Velocity velocity);      // Установка вектора скорости

    void setPosition(Point position);         // Мгновенное перемещение в указанную позицию

    void setSize(Dimension width, Dimension height); // Изменение размеров объекта

    void setMultiplyVelocity(float multiplier); // Умножение текущей скорости на множитель

    void resetVelocity();                     // Сброс скорости в ноль

    // Получение текущих параметров
    float getSpeedMultiplier() const;  // Текущий множитель скорости

    Velocity getVelocity() const;      // Текущий вектор скорости

    Point getPosition() const;         // Текущая позиция (центр)

    Size getDimensions() const;        // Текущие размеры (ширина и высота)

    // Работа с границами и коллизиями
    bool checkCollision(const Entity &other); // Проверка столкновения с другим объектом

    void updateBorders();            // Пересчет границ после изменения позиции/размера

    void updatePosition();           // Обновление позиции на основе текущей скорости

    // Получение границ объекта
    Coordinate getLeftBorder() const;   // Левая граница (минимальная x-координата)

    Coordinate getRightBorder() const;  // Правая граница (максимальная x-координата)

    Coordinate getTopBorder() const;    // Верхняя граница (максимальная y-координата)

    Coordinate getBottomBorder() const; // Нижняя граница (минимальная y-координата)

protected:
    // Внутреннее состояние объекта
    Point position;    // Позиция центра объекта

    Size size;        // Размеры (ширина и высота)

    Point borders[4];  // Границы объекта (4 вершины прямоугольника)
                       // Порядок: [0] левый-верхний, [1] правый-верхний
                       //         [2] правый-нижний,  [3] левый-нижний
    Velocity velocity; // Текущий вектор скорости

    float speedMultiplier = 1.0f; // Множитель скорости (по умолчанию 1)
};