#pragma once

enum Sides // индексация вершин прямоугольника
{
    LEFT_TOP = 0,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM
};

using Coordinate = float; // тип для координат
using Dimension = float; // тип для размеров
using Angle = float; // тип для углов
using Health = unsigned int; // тип для здоровья

struct Size // гарабирты
{
    Dimension width; // ширина
    Dimension height; // высота
};

struct Point // точка
{
    Coordinate x, y; // координаты
};

struct Normal // нормаль
{
    Coordinate x, y; // компоненты вектора нормали к поверхности
};

struct Velocity
{
    Coordinate x, y; // компоненты вектора скорости
  
};

constexpr Dimension PLATFORM_WIDTH = 0.2; // ширина платформы
constexpr Dimension PLATFORM_HEIGHT = 0.02; // высота платформы

Velocity calculateBounceDirection(Velocity old_velocty, Normal normal); // вычисление вектора скорости после упругого удара
void drawRectangle(Point* borders); // рисование прямоугольника по точкам границы

template<class T>
T getNorm(T x, T y); // вычисление нормы вектора

Coordinate dot(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // скалярное произведение векторов

Coordinate cross(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // векторное произведение векторов


