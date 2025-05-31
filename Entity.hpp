#include <GL/freeglut.h>

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
    void update(); //обновление координат и границ
    void setVelocity(); // установка скорости
    Velocity getVelocity(); // получение скорости
    void getPosition(); // получение позиции
    
    private:
    Point position; // позиция сущности (центр)
    Dimension width, height; // ширина и высота
    Point borders[4]; // Границы сущности (Координаты вершин прямоугольника);

};

