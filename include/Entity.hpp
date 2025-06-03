#pragma once

#include "utils.hpp" // вспомогательные типы, функции и константы

class Entity
{
public:
    Entity(Point position, Velocity velocity, Dimension width, Dimension height); // конструктор

    virtual void draw() = 0; // отрисовка сущности

    virtual void update() = 0; // обновление координат и границ

    void setVelocity(Velocity velocity); // установка скорости

    Velocity getVelocity() const; // получение скорости

    Point getPosition() const; // получение позиции

    Size getDimensions() const; // получение габаритов

    void checkCollision(const Entity &other) const; // проверка на столкновение с другой сущностью

    Point *getBorders(); // получение границ

    void updateBorders(); // обновление границ

    void updatePosition(); // обновление позиции

protected:
    Point position; // позиция сущности (центр)

    Size size; // ширина и высота

    Point borders[4]; // границы сущности (Координаты вершин прямоугольника)

    Velocity velocity; // скорость сущности
};
