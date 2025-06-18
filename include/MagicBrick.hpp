#pragma once
// Подключение заголовочного файла базового класса Brick
#include "Brick.hpp"

// Класс MagicBrick - магический кирпич, наследуется от Brick
// Особенности:
// 1) Графическим представлением (особая текстура/цвет)
// 2) При разрушении создает падающий бонус
class MagicBrick : public Brick
{
public:
    // Конструктор магического кирпича
    // position - координаты левого верхнего угла
    // width, height - размеры кирпича
    // health - количество здоровья
    MagicBrick(Point position, Dimension width, Dimension height, Health health);

    // Переопределенный метод отрисовки
    // Реализует особый внешний вид магического кирпича
    void draw() override;
};