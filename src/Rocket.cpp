#include "Rocket.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <cmath>
#include "utils.hpp"

// Конструктор ракеты: инициализация позиции, скорости, размеров и статусов
Rocket::Rocket(Point position, Dimension width, Dimension height)
    : Entity(position, ROCKET_SPEED, width, height), targeting(false) {
        boomStatus = false; // ракета не взорвана
    }

// Установить цель для ракеты (позиция платформы)
void Rocket::setTarget(const Platform &platform)
{
    targetPosition = platform.getPosition();
    targeting = true;
}

// Запустить ракету по прямой (без наведения)
void Rocket::launchStraight()
{
    targeting = false;
}

// Обновление состояния ракеты (движение к цели или по прямой)
void Rocket::update()
{
    if (targeting and !shieldBounce)
    {
        // Движение к платформе
        float dx = targetPosition.x - position.x;
        float dy = targetPosition.y - position.y;
        float dist = getNorm(dx,dy);
        // Если ракета в зоне плиток — наводится, иначе летит прямо
        if (position.y >= MAP_POSITION.y - MAP_SIZE.height + PLATFORM_ZONE)
        {
            velocity.x = getNorm(ROCKET_SPEED.x, ROCKET_SPEED.y) * dx/dist;
            velocity.y = getNorm(ROCKET_SPEED.x, ROCKET_SPEED.y) * dy/dist;
        }
        else
        {
            launchStraight();
        }
    }
    updatePosition();   // обновляем позицию
    updateBorders();    // обновляем границы
}

// Обработка столкновения с платформой
void Rocket::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        const_cast<Platform&>(platform).hit(); // снимаем константность для нанесения урона
        isHit = true; // ракета попала в платформу
    }
}

// Отрисовка ракеты с поворотом по направлению движения
void Rocket::draw()
{
    Dimension normv = getNorm(velocity.x ,velocity.y);
    Coordinate cosv = velocity.x / normv;
    Coordinate sinv = velocity.y / normv;
    glPushMatrix();
    DrawTexturedRectangle(ROCKET_TEXTURE, this->position, size, 180/M_PI*getAngle(cosv, sinv)-90);
    glPopMatrix();
}

// Проверка, взорвалась ли ракета
bool Rocket::isBoom()
{
    return boomStatus;
}

// Взорвать ракету (установить статус взрыва)
void Rocket::Boom()
{
    boomStatus = true;
}

// Обработка столкновения с щитом платформы (отскок)
void Rocket::Collision(const Shield &shield)
{
    Normal normal;
    Coordinate x = (position.x - shield.getPosition().x) / (shield.getDimensions().width / 2 + this->getDimensions().width / 2);
    Coordinate y = (position.y - shield.getPosition().y) / (shield.getDimensions().height / 2 + this->getDimensions().height / 2);
    if (abs(x) <= abs(y))
        normal = {0, y / abs(y)};
    else if (abs(x) >= abs(y))
        normal = {x / abs(x), 0};
    else if (abs(x) == abs(y))
        normal = {x / abs(x), y / abs(y)};
    this->setVelocity(calculateBounceDirection(this->getVelocity(), normal));
}

// Установить статус "отскочила от щита"
void Rocket::Bounce()
{
    shieldBounce = true;
}