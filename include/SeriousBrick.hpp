#pragma once

#include "Brick.hpp"  // Базовый класс Brick

// Класс SeriousBrick - прочный кирпич
// Особенности:
// - Требует 2 удара для разрушения
// - Меняет внешний вид при каждом попадании
class SeriousBrick : public Brick 
{
public:
    // Создает прочный кирпич
    // position - позиция центра
    // width - ширина кирпича
    // height - высота кирпича
    SeriousBrick(Point position, Dimension width, Dimension height);

    // Отрисовывает кирпич с учетом текущего состояния
    // Реализует анимацию повреждений при получении ударов
    void draw() override;
};