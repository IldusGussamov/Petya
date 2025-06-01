#pragma once
#include "Entity.hpp"

class Brick : public Entity
{
protected:
    int health;     // Здоровье
    bool destroyed; // сломан иль нет
    
public:
    Brick(Point position, Dimension width, Dimension height, int health);

    int getHealth() const; // кол-во хп

    bool isDestroyed() const; // унчтожен ли

    void takeDamage(int damage); // изменение хп

    // Изменение дефолт функций
    void update() override;
    void draw() override;

    // Обновляет границы кирпича (вызывается при изменении позиции/размера)
    void updateBorders();
};
