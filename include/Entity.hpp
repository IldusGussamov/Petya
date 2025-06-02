#pragma once
#include "utils.hpp"


class Entity
{
    public:
    Entity(Point position, Velocity velocity, Dimension width, Dimension height); // конструктор

    virtual void draw() = 0; // Отрисовка сущности
    virtual void update() = 0; //обновление координат и границ

    void setVelocity(Velocity velocity); // установка скорости
    Velocity getVelocity() const; // получение скорости
    Point getPosition() const; // получение позиции
    Size getDimensions() const; // получение габаритов
    void checkCollision(const Entity& other) const; // проверка на столкновение с другой сущностью
    Point* getBorders();
    void updateBorders();
    void updatePosition();

    protected:
    Point position; // позиция сущности (центр)
    Size size; // ширина и высота
    Point borders[4]; // Границы сущности (Координаты вершин прямоугольника);
    Velocity velocity; // скорость сущности

};

