#pragma once

enum Sides
{
    LEFT_TOP = 0,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM
};

using Coordinate = float; // тип для координат и компонент векторов
using Dimension = float; // тип для ширины/высоты

struct Size
{
    Dimension width;
    Dimension height;
};

struct Point // точка
{
    Coordinate x, y; // компоненты
};

struct Velocity // вектор скорости
{
    Coordinate x, y; // компоненты
};

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

    protected:
    Point position; // позиция сущности (центр)
    Size size; // ширина и высота
    Point borders[4]; // Границы сущности (Координаты вершин прямоугольника);
    Velocity velocity; // скорость сущности

};

