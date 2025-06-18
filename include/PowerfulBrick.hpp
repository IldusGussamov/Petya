#pragma once

#include "Brick.hpp"  // Базовый класс Brick

// Класс PowerfulBrick - усиленный кирпич
// Особенности:
// - Требует 3 удара для разрушения
// - Меняет внешний вид при каждом попадании
class PowerfulBrick : public Brick
{
public:
    // Создает усиленный кирпич
    // position - позиция центра
    // width - ширина кирпича
    // height - высота кирпича
    PowerfulBrick(Point position, Dimension width, Dimension height);

    // Отрисовывает кирпич с учетом текущего состояния
    // Реализует анимацию повреждений при получении ударов
    void draw() override;
};