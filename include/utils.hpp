#pragma once
#include <math.h>

enum Sides // индексация вершин прямоугольника
{
    LEFT_TOP = 0, // левая верхняя вершина
    RIGHT_TOP,    // правая верхняя вершина
    RIGHT_BOTTOM, // правая нижняя вершина
    LEFT_BOTTOM   // левая нижняя вершина
};

using Coordinate = float;    // тип для координат
using Dimension = float;     // тип для размеров
using Angle = float;         // тип для углов
using Health = int; // тип для здоровья

struct Size // гарабирты
{
    Dimension width;  // ширина
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

constexpr Point MAP_POSITION{-0.9, 0.9};                                                                                         // позиция карты
constexpr Size MAP_SIZE{1, 1.8};                                                                                                 // размеры карты
constexpr Dimension PLATFORM_ZONE = MAP_SIZE.height * 0.3;                                                                       // высота свободной области
constexpr Dimension PLATFORM_WIDTH = 0.2;                                                                                        // ширина платформы
constexpr Dimension PLATFORM_HEIGHT = 0.02;                                                                                      // высота платформы
constexpr Coordinate PLATFORM_SPEED = 0.1 * 0.35 * 0.3;                                                                          // скорость платформы
constexpr Point PLATFORM_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, MAP_POSITION.y - MAP_SIZE.height + PLATFORM_ZONE / 2}; // начальная позиция платформы относительно игрового поля
constexpr Angle MAX_BOUNCE_ANGLE = M_PI * 0.4;                                                                                   // максимальный угол отскока мяча от платформы
constexpr Coordinate BALL_SPEED = 0.02; // скорость мяча
constexpr Dimension BALL_SIZE = 0.01 * MAP_SIZE.height; // диаметр мяча
constexpr Point BALL_START_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, PLATFORM_POSITION.y + PLATFORM_HEIGHT / 2 + BALL_SIZE / 2}; // начальные координаты мяча

extern bool isGameOver;

// скорость мяча
Velocity calculateBounceDirection(Velocity old_velocty, Normal normal); // вычисление вектора скорости после упругого удара

void drawBorderRectangle(Point *borders);      // рисование прямоугольника по точкам границы
void drawRectangle(Point position, Size size); // рисование прямоугольника по позиции (левая верхняя вершина) и размеру (Ox вправо, а Oy вниз)

template <class T>
T getNorm(T x, T y); // вычисление нормы вектора

Velocity rotateVelocity(Velocity old_velocity, Angle angle); // поворот вектора скорости

Coordinate dot(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // скалярное произведение векторов

Coordinate cross(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // векторное произведение векторов

Velocity calculateBounceDirectonPlatform(Velocity old_velocity, Coordinate difference, Dimension PLATFORM_W = PLATFORM_WIDTH); // вычисление скорости после отскока от платформы

Angle calculateAngleBetweenVectors(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // вычисление угла между векторами
