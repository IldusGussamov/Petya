#pragma once

#include "Brick.hpp"

#include <vector>

#include <CombatBrick.hpp>


class MapGenerator
{
private:

    Point position; // Позиция левого верхнего угла карты

    bool randomFlag = true; // Флаг для случайной генерации кирпичей

    std::vector<Brick*> bricks; // Указатели на все кирпичи (используется полиморфизм)

public:
    // Основные методы
    MapGenerator(Point position, bool flag);

    ~MapGenerator(); // Деструктор для очистки памяти

    // Геттеры

    std::vector<Brick*> getBricks(); // Получение вектора кирпичей

    std::vector<Brick*> generateBricksRandom(Point position); // Генерация кирпичей с использованием случайных значений

    std::vector<Brick*> generateBricksFromFile(Point position); // Генерация кирпичей из файла

    void generateBricks(); // Генерация кирпичей на карте
};