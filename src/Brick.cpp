// #include "Brick.hpp"
// #include <GL/glut.h>
// #include <utils.hpp>

// Brick::Brick(Point position, Dimension width, Dimension height, Health health)
//     : Entity(position, Velocity{0, 0}, width, height), health(health), destroyed(false)
// {
//     updateBorders();
// }

// Health Brick::getHealth() const
// {
//     return health;
// }

// bool Brick::isDestroyed() const
// {
//     return destroyed;
// }

// void Brick::takeDamage(int damage)
// {
//     if (!destroyed)
//     {
//         health -= damage;
//         if (health <= 0)
//         {
//             health = 0;
//             destroyed = true;
//         }
//     }
// }

// void Brick::update()
// {
//     if (health <= 0)
//     {
//         destroyed = true;
//     }
// }

// void Brick::draw() 
// {
//     // if (destroyed)
//     //     return;

//     // // цвета для различия прочности
//     // if (health >= 3)
//     // {
//     //     glColor3f(1.0f, 0.0f, 0.0f); // красный
//     // }
//     // else if (health == 2)
//     // {
//     //     glColor3f(1.0f, 1.0f, 0.0f); // жёлтый
//     // }
//     // else
//     // {
//     //     glColor3f(0.0f, 0.0f, 1.0f); // синий
//     // }

//     // drawBorderRectangle(borders);
// }
#include "Brick.hpp"
#include "Map.hpp"
#include <GL/glut.h>
#include <algorithm>

Brick::Brick(Point position, Dimension width, Dimension height, Health health)
    : Entity(position, Velocity{0, 0}, width, height), 
      health(health), destroyed(false), 
      havePattern(false), currentPattern(0)
{
    updateBorders();
    // Инициализация паттерна нулями
    movePattern[0] = movePattern[1] = movePattern[2] = movePattern[3] = 0;
}

void Brick::setMovePattern(int left, int right, int up, int down) {
    movePattern[0] = left;
    movePattern[1] = right;
    movePattern[2] = up;
    movePattern[3] = down;
    havePattern = true;
}

// Эти функции скорее всего нужно вынести в мапу
// bool Brick::canMove(int direction, const std::vector<Brick*>& bricks, const Map& map) const {
//     if (!havePattern) return false;
    
//     Point newPos = position;
//     switch(direction) {
//         case 0: newPos.x -= BRICK_WIDTH; break; // Влево
//         case 1: newPos.x += BRICK_WIDTH; break; // Вправо
//         case 2: newPos.y += BRICk_HEIGHT; break; // Вверх
//         case 3: newPos.y -= BRICk_HEIGHT; break; // Вниз
//     }
    
//     // Проверка границ карты
//     if (newPos.x - size.width/2 < map.getLeftBorder() || 
//         newPos.x + size.width/2 > map.getRightBorder() ||
//         newPos.y + size.height/2 > map.getTopBorder() || 
//         newPos.y - size.height/2 < map.getButtomBorder()) {
//         return false;
//     }
    
//     // Проверка коллизий с другими кирпичами
//     for (const Brick* brick : bricks) {
//         if (brick != this) {
//             Entity temp(newPos, {0,0}, size.width, size.height);
//             if (temp.checkCollision(*brick)) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void Brick::moveByPattern(const std::vector<Brick*>& bricks, const Map& map) {
//     if (!havePattern || brickMoveCounter % 2 != 0) return; // Двигаем каждый 2-й вызов
    
//     for (int i = 0; i < 4; ++i) {
//         int patternIndex = (currentPattern + i) % 4;
//         if (movePattern[patternIndex] > 0 && canMove(patternIndex, bricks, map)) {
//             switch(patternIndex) {
//                 case 0: position.x -= BRICK_WIDTH; break;
//                 case 1: position.x += BRICK_WIDTH; break;
//                 case 2: position.y += BRICk_HEIGHT; break;
//                 case 3: position.y -= BRICk_HEIGHT; break;
//             }
//             movePattern[patternIndex]--;
//             currentPattern = (patternIndex + 1) % 4;
//             updateBorders();
//             break;
//         }
//     }
// }

void Brick::update() {
    if (health <= 0) {
        destroyed = true;
    }
}

void Brick::draw() {
    if (destroyed) return;
    
    // Отрисовка кирпича (ваш существующий код)
}
