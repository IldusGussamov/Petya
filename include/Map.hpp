#pragma once
#include "Platform.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include <vector>

class Map
{
private:
    Point position;            // позиция карты (левая верхняя вершина)
    Size size;                 // размер карты (Ox вправо, а Oy вниз)
    std::vector<Ball> balls;   // мячи
    std::vector<Brick*> bricks; // плитки
    bool isThrowBall = false;  // статус полета мяча

    // // Костя - как увидишь, Ильдус, удали это коммент
    BrickMoveCounter BMC = 0;  // Счетчик движения кирпичей

public:
    Platform platform;         // платформа

    Map(Point position, Size size); // конструктор
    void draw();                    // отрисовка карты
    void update();                  // обновление карты
    void throwBall();               // бросок мяча
    void bounceOffWalls();          // проверка столкновения о стену и отскок мяча
    void generateBricks();          // генерация плиток
    void addBall();
    void resetMap(); // сброс карты

    // Новые методы для управления кирпичами//Костя, 2 функции
    void moveBricksByPatterns(); // Основной метод движения кирпичей
    bool canBrickMove(const Brick* brick, int direction) const; // Проверка возможности движения

    Coordinate getLeftBorder();   // получение левой границы
    Coordinate getRightBorder();  // получение правой границы
    Coordinate getTopBorder();    // получение верхней границы
    Coordinate getButtomBorder(); // получение нижней границы

    bool isBallThrown() const; // проверка на то, что мяч брошен

    Point getPosition(); // получение позиции карты
    Size getSize();      // получение размеров карты
};