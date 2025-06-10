#include "Map.hpp"
#include "utils.hpp"
#include "PowerfulBrick.hpp"
#include <GL/freeglut.h>

Map::Map(Point position, Size size) : platform(PLATFORM_POSITION, {0, 0})
{
    this->position = position;
    this->size = size;
    PowerfulBrick brick{{position.x + size.width / 2 + 0.3, position.y - size.height / 3}, 0.2, 0.1};
    PowerfulBrick brick1{{position.x + size.width / 2 - 0.3, position.y - size.height / 3}, 0.2, 0.1};
    PowerfulBrick brick2{{position.x + size.width / 2, position.y - size.height / 3 + 0.3}, 0.2, 0.1};
    PowerfulBrick brick3{{position.x + size.width / 2, position.y - size.height / 3 - 0.3}, 0.2, 0.1};
    bricks.push_back(brick);
    bricks.push_back(brick1);
    bricks.push_back(brick2);
    bricks.push_back(brick3);
}

void Map::draw()
{
    glColor3f(1, 1, 1);
    drawRectangle(position, size);
    platform.draw();
    for (Brick &brick : bricks)
    {
        brick.draw();
    }
    for (Ball &ball : balls)
    {
        ball.draw();
    }
}

void Map::update()
{
    if (!balls.size())
    {
        platform.hit();
        this->isThrowBall = false;
        platform.setPosition(PLATFORM_POSITION);
        if (platform.getHealth())
            this->balls.emplace_back(BALL_START_POSITION, platform.getVelocity(), BALL_SIZE);
    }
    platform.update();
    for (Ball &ball : balls)
    {
        ball.draw();
    }
    bounceOffWalls();
    for (Ball &ball : balls)
    {
        ball.Collision(platform);
        for (Brick &brick : bricks)
        {
            Velocity old_vel = ball.getVelocity();
            ball.Collision(brick);
            Velocity new_vel = ball.getVelocity();
            if (old_vel.x != new_vel.x || old_vel.y != new_vel.y)
                brick.takeDamage(1);
        }
        if (!this->isThrowBall)
        {
            ball.setVelocity(platform.getVelocity());
        }
        ball.update();
    }
}

void Map::throwBall()
{
    this->isThrowBall = true;
    this->balls[0].setVelocity({0, BALL_SPEED});
}

void Map::bounceOffWalls()
{
    for (int i = 0; i < balls.size(); ++i)
    {
        Ball &ball = balls[i];
        if (ball.getLeftBorder() <= this->getLeftBorder()) // столкновения мяча с левой границей карты
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {1, 0}));

        if (ball.getRightBorder() >= this->getRightBorder()) // столкновение мяча с правой границей карты
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {-1, 0}));

        if (ball.getTopBorder() >= this->getTopBorder()) // столкновение мяча с верхней границей карты
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {0, -1}));

        if (ball.getBottomBorder() <= this->getButtomBorder()) // столкновение мяча с нижней границей карты
            balls.erase(balls.begin() + i);                    // удаление мяча, если он упал за нижнюю границу карты
    }
}

Coordinate Map::getLeftBorder()
{
    return position.x;
}
Coordinate Map::getRightBorder()
{
    return position.x + size.width;
}
Coordinate Map::getTopBorder()
{
    return position.y;
}
Coordinate Map::getButtomBorder()
{
    return position.y - size.height;
}

bool Map::isBallThrown() const
{
    return isThrowBall;
}