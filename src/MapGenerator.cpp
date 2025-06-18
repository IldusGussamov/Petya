#include "MapGenerator.hpp"
#include "utils.hpp"
#include "PowerfulBrick.hpp"
#include "SimpleBrick.hpp"
#include "SeriousBrick.hpp"
#include "CombatBrick.hpp"
#include <GL/freeglut.h>
#include <random>
#include "MagicBrick.hpp"

MapGenerator::MapGenerator(Point position, bool flag)
    : randomFlag(flag)
{  
    this->position = position;
    if (randomFlag)
    {
        bricks = generateBricksRandom(position);
    }
    else
    {
        bricks = generateBricksFromFile(position);
    }
}

MapGenerator::~MapGenerator()
{
    for (Brick *brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
}

std::vector<Brick *> MapGenerator::getBricks()
{
    return bricks;
}

void MapGenerator::generateBricks() // Генерация кирпичей на карте
{
    if (randomFlag)
    {
        bricks = generateBricksRandom(position);
    }
    else
    {
        bricks = generateBricksFromFile(position);
    }
}



// Генерация кирпичей на карте с использованием случайных значений
std::vector<Brick *> MapGenerator::generateBricksRandom(Point position) // Позиция - левый верхний угол карты
{
    Point actualPosition = {position.x + BRICK_WIDTH / 2, position.y - BRICk_HEIGHT / 2};
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            std::uniform_int_distribution<int> dist(1, 120);
            int randomValue = dist(gen);

            // Добавление различных типов кирпичей по вероятности
            if (randomValue < 3)
            {
                bricks.push_back(new MagicBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 3));
            }
            if (randomValue >= 113)
            {
                bricks.push_back(new MagicBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 2));
            }
            if (randomValue >= 3 and randomValue < 4)
            {
                bricks.push_back(new MagicBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 1));
            }
            if (randomValue >= 70 and randomValue < 75)
            {
                bricks.push_back(new SimpleBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }
            if (randomValue >= 75 and randomValue < 85)
            {
                bricks.push_back(new SeriousBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }
            if (randomValue >= 85 and randomValue < 90)
            {
                bricks.push_back(new PowerfulBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }
            // Добавление боевых кирпичей в центре поля
            if ((ROWS - ROWS / 5 > i and i > ROWS / 5) and (COLS - COLS / 5 > j and j > COLS / 5))
            {
                if (randomValue >= 90 and randomValue < 99)
                {
                    bricks.push_back(new CombatBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 1));
                }
                if (randomValue >= 99 && randomValue < 110)
                {
                    bricks.push_back(new CombatBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 2));
                }
                if (randomValue >= 110 && randomValue <= 113)
                {
                    bricks.push_back(new CombatBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 2));
                }
            }
            // Случайно делаем некоторые кирпичи движущимися
            if (!bricks.empty() && dist(gen) > 90)
            {
                Coordinate speed = BALL_SPEED * 0.1;
                if (dynamic_cast<CombatBrick *>(bricks.back()))
                    speed *= 0.4;
                bricks.back()->setMovePattern(speed, PLATFORM_WIDTH, dist(gen) % 4);
            }
            actualPosition.x += BRICK_WIDTH;
        }
        actualPosition.x = position.x + BRICK_WIDTH / 2;
        actualPosition.y -= BRICk_HEIGHT;
    }
    return bricks;
}

std::vector<Brick *> MapGenerator::generateBricksFromFile(Point position) // Генерация кирпичей из файла
{
    return bricks;
} 