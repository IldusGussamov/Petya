#pragma once
// Подключение заголовочного файла базового класса Brick
#include "Brick.hpp"

// Класс CombatBrick - боевой кирпич, наследуется от Brick
// Отличается от обычного кирпича:
// 1) Графическим представлением (особая текстура/цвет)
// 2) После уничтожения запускает ракету
class CombatBrick : public Brick
{
public:
    // Конструктор боевого кирпича
    // position - координаты левого верхнего угла
    // width, height - размеры кирпича
    // health - количество здоровья
    CombatBrick(Point position, Dimension width, Dimension height, Health health);

    // Переопределенный метод отрисовки
    // Реализует особый внешний вид боевого кирпича
    void draw() override;
};