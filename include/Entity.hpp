#pragma once

using Coordinate = float; // тип для координат и компонент векторов
using Dimension = float; // тип для ширины/высоты

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
    
    protected:
    Point position; // позиция сущности (центр)
    Dimension width, height; // ширина и высота
    Point borders[4]; // Границы сущности (Координаты вершин прямоугольника);
    Velocity velocity; // скорость сущности

};

