#pragma once
#include "Platform.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include "Rocket.hpp"
#include <vector>
#include <CombatBrick.hpp>
#include "Bonus.hpp"

class Map
{
private:
    Point position;            // позиция карты (левая верхняя вершина)
    Size size;                 // размер карты (Ox вправо, а Oy вниз)
    std::vector<Ball> balls;   // мячи
    std::vector<Brick*> bricks; // плитки
    std::vector<Rocket> rockets; // Хранение ракет на карте
    std::vector<Bonus> bonuses; // бонусы

    bool isThrowCapture = true;
    bool isThrowBall = false;  // статус полета мяча

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
    void resetBonuses(); // сброс бонусов
    void rotateLeftdirectionThrowBall(); // поворот направления броска мяча влево
    void rotateRightdirectionThrowBall(); // поворот направления броска мяча вправо 

    Angle directionThrowBall; // направление броска мяча

    Coordinate getLeftBorder();   // получение левой границы
    Coordinate getRightBorder();  // получение правой границы
    Coordinate getTopBorder();    // получение верхней границы
    Coordinate getButtomBorder(); // получение нижней границы

    bool isActivateStickingBonus; // флаг активации бонуса "липучка"

    bool isBallThrown() const; // проверка на то, что мяч брошен
    bool isCaptureThrown() const;

    Point getPosition(); // получение позиции карты
    Size getSize();      // получение размеров карты
};