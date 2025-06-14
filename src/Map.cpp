#include "Map.hpp"
#include "utils.hpp"
#include "PowerfulBrick.hpp"
#include "SimpleBrick.hpp"
#include "SeriousBrick.hpp"
#include <GL/freeglut.h>
#include <iostream>
#include <random>

Map::Map(Point position, Size size) : platform(PLATFORM_POSITION, {0, 0})
{
    this->position = position;
    this->size = size;
    this->generateBricks();
}

void Map::generateBricks()
{
    Point actualPosition = {position.x + BRICK_WIDTH / 2, position.y - BRICk_HEIGHT / 2};
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            std::uniform_int_distribution<int> dist(1, 100);
            int randomValue = dist(gen);
            if (randomValue >= 70 and randomValue < 75)
            {
                bricks.push_back(new SimpleBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }
            if (randomValue >= 75 and randomValue < 85)
            {
                bricks.push_back(new SeriousBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }

            if (randomValue >= 85)
            {
                bricks.push_back(new PowerfulBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }

            actualPosition.x += BRICK_WIDTH;
        }
        actualPosition.x = position.x + BRICK_WIDTH / 2;
        actualPosition.y -= BRICk_HEIGHT;
    }
}

void Map::draw()
{
    drawRectangle(position, size);
    platform.draw();
    for (Brick *brick : bricks)
    {
        brick->draw();
    }
    for (Ball &ball : balls)
    {
        ball.draw();
    }
}

void Map::update()
{
    if (isGameOver)
        return;

    if (bricks.size() == 0)
    {
        isGameOver = true;
        return;
    }

    if (!balls.size())
    {
        platform.hit();
        this->isThrowBall = false;
        platform.setPosition(PLATFORM_POSITION);
        if (platform.getHealth())
            this->balls.emplace_back(BALL_START_POSITION, platform.getVelocity(), BALL_SIZE);
        else
        {
            isGameOver = true; // если платформа уничтожена, то игра окончена
            return;
        }
    }

    platform.update();

    bounceOffWalls();

    for (int i = 0; i < bricks.size();)
    {
        if (!bricks[i]->getHealth())
        {
            delete bricks[i];
            bricks.erase(bricks.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    for (Ball &ball : balls)
    {
        if (!this->isThrowBall)
        {
            ball.setVelocity(platform.getVelocity());
        }
        else
        {
            ball.Collision(platform);
            bool flag = false;
            for (Brick *brick : bricks)
            {
                Velocity old_vel = ball.getVelocity();
                flag = (ball.Collision(*brick));
                Velocity new_vel = ball.getVelocity();
                if (old_vel.x != new_vel.x || old_vel.y != new_vel.y)
                    brick->takeDamage(1);
                if (flag)
                {
                    flag = false;
                    break;
                }
            }
        }
        ball.update();
    }
}

void Map::throwBall()
{
    this->isThrowBall = true;
    this->balls[0].setVelocity(rotateVelocity({0, BALL_SPEED}, 3.14 / 8));
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

void Map::addBall()
{
    if (!isBallThrown())
        return;
    std::vector<Ball> extraBalls;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (Ball ball : balls)
    {
        float randomValue = dist(gen);
        extraBalls.emplace_back(ball.getPosition(), rotateVelocity(ball.getVelocity(),2* M_PI*randomValue/100), BALL_SIZE);
    }
    balls.insert(balls.end(), extraBalls.begin(), extraBalls.end());
}

void Map::resetMap()
{
    isGameOver = false;
    platform = Platform(PLATFORM_POSITION, {0, 0});
    balls.clear();
    isThrowBall = false;
    for (Brick *brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
    generateBricks();
}