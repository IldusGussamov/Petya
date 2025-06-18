#pragma once

#include "Brick.hpp"  // Базовый класс для кирпичей

// Класс SimpleBrick - базовый тип разрушаемого кирпича
// Особенности:
// - Разрушается за 1 удар
// - Имеет стандартный цвет/текстуру
class SimpleBrick : public Brick
{
public:
    // Создает простой кирпич в указанной позиции
    // position - координаты центра
    // width - ширина кирпича
    // height - высота кирпича
    SimpleBrick(Point position, Dimension width, Dimension height);

    // Отрисовывает кирпич с использованием стандартного внешнего вида
    // Реализация должна использовать базовый цвет/текстуру простого кирпича
    void draw() override;
};