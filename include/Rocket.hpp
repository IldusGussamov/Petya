#pragma once

#include "Entity.hpp"  // Базовый класс Entity

#include "Platform.hpp"  // Класс Platform для определения цели

// Класс Rocket представляет ракету, которая может:
// - Лететь прямо вниз
// - Наводиться на платформу
// - Отскакивать от щита
// - Взрываться при столкновении
class Rocket : public Entity 
{
public:
    // Создает ракету в указанной позиции с заданными размерами
    Rocket(Point position, Dimension width, Dimension height);

    // Устанавливает цель для наведения (платформу)
    void setTarget(const Platform &platform);

    // Запускает ракету прямо вниз без наведения
    void launchStraight();

    // Обновляет состояние ракеты (положение, проверка столкновений)
    void update() override;

    // Отрисовывает ракету с учетом ее состояния
    void draw() override;

    // Проверяет, взорвалась ли ракета
    bool isBoom();

    // Активирует взрыв ракеты
    void Boom();

    // Обрабатывает столкновение со щитом (отскок)
    void Collision(const Shield &shield);

    // Обрабатывает столкновение с платформой (взрыв)
    void Collision(const Platform &platform);

    // Обрабатывает отскок ракеты
    void Bounce();

private:

    bool targeting;        // Флаг режима наведения на цель

    Point targetPosition;  // Позиция цели (для наведения)

    bool shieldBounce;     // Флаг отскока от щита

    bool boomStatus;       // Флаг состояния взрыва

protected:
    bool isHit;           // Флаг попадания в платформу
};