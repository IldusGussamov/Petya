#pragma once

// Подключение необходимых заголовочных файлов
#include "Entity.hpp"    // Базовый класс Entity

#include "Platform.hpp"  // Класс Platform для обработки столкновений

// Класс Bonus, представляющий игровой бонус, наследуется от Entity
class Bonus : public Entity 
{
public:
    // Конструктор с параметрами:
    // position - начальная позиция бонуса
    // width - ширина бонуса
    // height - высота бонуса
    Bonus(Point position, Dimension width, Dimension height);

    // Метод отрисовки бонуса (переопределение виртуального метода Entity)
    void draw() override;

    // Метод обновления состояния бонуса (переопределение виртуального метода Entity)
    void update() override;

    // Метод обработки столкновения с платформой
    void Collision(const Platform &platform);

    // Метод получения типа бонуса
    // Возвращает целочисленный идентификатор типа бонуса
    int getBonusType() const;

    // Флаг, указывающий был ли бонус подобран
    bool isHit = false;

protected:
    // Тип бонуса (0 - базовый тип, может быть переопределен в производных классах)
    int bonusType = 0;
};