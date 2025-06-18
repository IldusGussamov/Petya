#pragma once

#include "Platform.hpp"

#include "Ball.hpp"

#include "Brick.hpp"

#include "Rocket.hpp"

#include <vector>

#include <CombatBrick.hpp>

#include "Bonus.hpp"

// Класс Map представляет игровое поле и управляет всеми объектами на нем
// Отвечает за:
// - Хранение и отрисовку всех игровых объектов
// - Обработку физики и столкновений
// - Генерацию и управление бонусами
// - Управление состоянием игры
class Map
{
private:
    // Основные параметры карты
    Point position;            // Позиция левого верхнего угла карты

    Size size;                 // Размеры карты (ширина и высота)

    // Коллекции игровых объектов
    std::vector<Ball> balls;   // Все активные мячи на карте

    std::vector<Brick*> bricks; // Указатели на все кирпичи (используется полиморфизм)

    std::vector<Rocket> rockets; // Активные ракеты (от боевых кирпичей)

    std::vector<Bonus> bonuses; // Активные бонусы, падающие вниз

    // Флаги состояния
    bool isThrowCapture = true; // Флаг режима "захвата" мяча платформой

    bool isThrowBall = false;   // Флаг, указывающий что мяч в полете

public:
    Platform platform;         // Игровая платформа

    // Основные методы
    Map(Point position, Size size); // Инициализация карты с заданными параметрами
    
    void draw();                    // Отрисовка всех объектов карты

    void update();                  // Обновление состояния всех объектов

    void throwBall();               // Запуск мяча с платформы

    void bounceOffWalls();          // Обработка отскоков мячей от стен

    void generateBricks();          // Создание уровня из кирпичей

    void addBall();                 // Добавление нового мяча в игру

    void resetMap();                // Полный сброс состояния карты

    void resetBonuses();            // Удаление всех бонусов

    // Управление направлением броска
    void rotateLeftdirectionThrowBall();  // Поворот направления броска против часовой

    void rotateRightdirectionThrowBall(); // Поворот направления броска по часовой

    Angle directionThrowBall; // Текущий угол направления броска мяча

    // Границы игрового поля
    Coordinate getLeftBorder();   // Левая граница (минимальная X-координата)

    Coordinate getRightBorder();  // Правая граница (максимальная X-координата)

    Coordinate getTopBorder();    // Верхняя граница (минимальная Y-координата)

    Coordinate getButtomBorder(); // Нижняя граница (максимальная Y-координата)

    // Состояния бонусов
    bool isActivateStickingBonus; // Флаг активного бонуса "липучка" для платформы

    // Проверки состояния
    bool isBallThrown() const;    // Проверка, находится ли мяч в полете

    bool isCaptureThrown() const; // Проверка режима захвата мяча

    ~Map(); // Деструктор для очистки памяти

    // Геттеры
    Point getPosition(); // Получение позиции карты
    
    Size getSize();      // Получение размеров карты
};