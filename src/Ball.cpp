#include "Ball.hpp"
#include "Platform.hpp"
#include <GL/freeglut.h>
#include <iostream>

// Конструктор шара: инициализация позиции, скорости и размера
Ball::Ball(Point position, Velocity velocity, Dimension size) : Entity(position, velocity, size, size)
{
    isStick = false; // по умолчанию шар не "липкий"
}

// Отрисовка шара
void Ball::draw()
{  
    glColor3f(1, 1, 1); // сброс цвета
    DrawTexturedRectangle(BALL_TEXTURE, position, size, rotate); // рисуем текстурированный шар
}

// Обновление позиции шара и вращения
void Ball::update()
{
    this->position.x += this->velocity.x * speedMultiplier; // движение по X
    this->position.y += this->velocity.y * speedMultiplier; // движение по Y
    rotate += 1; // увеличиваем угол вращения
    updateBorders(); // обновляем границы шара
}

// Проверка и обработка столкновения с платформой
bool Ball::Collision(const Platform &platform)
{
    if (this->checkCollision(platform))
    {
        // Пересчитываем скорость после отскока от платформы
        this->setVelocity(calculateBounceDirectonPlatform(this->getVelocity(), platform.getPosition().x - this->position.x, platform.getDimensions().width));
        return true;
    }
    return false;
}

// Проверка и обработка столкновения с кирпичом
bool Ball::Collision(const Brick &brick)
{
    if (this->checkCollision(brick))
    {
        Normal normal;
        // Вычисляем нормаль к поверхности столкновения
        Coordinate x = (position.x - brick.getPosition().x) / (brick.getDimensions().width / 2 + this->getDimensions().width / 2);
        Coordinate y = (position.y - brick.getPosition().y) / (brick.getDimensions().height / 2 + this->getDimensions().height / 2);
        if (abs(x) <= abs(y))
            normal = {0, y / abs(y)};
        else if (abs(x) >= abs(y))
            normal = {x / abs(x), 0};
        else if (abs(x) == abs(y))
            normal = {x / abs(x), y / abs(y)};
        // Пересчитываем скорость после отскока от кирпича
        this->setVelocity(calculateBounceDirection(this->getVelocity(), normal));
        return true;
    }
    return false;
}

// Сделать шар "липким" (прилипает к платформе)
void Ball::stick()
{
    isStick = true;
}

// Получить статус "липкости" шара
bool Ball::getStick()
{
    return isStick;
}

// Установить статус "липкости" шара
void Ball::setStick(bool status)
{
    isStick = status;
}