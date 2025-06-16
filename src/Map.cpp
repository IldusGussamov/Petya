#include "Map.hpp"
#include "utils.hpp"
#include "PowerfulBrick.hpp"
#include "SimpleBrick.hpp"
#include "SeriousBrick.hpp"
#include "CombatBrick.hpp"
#include "Rocket.hpp"
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
            if (randomValue >= 75 and randomValue < 95)
            {
                bricks.push_back(new SeriousBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT));
            }

            if (randomValue >= 95)
            {
                combatBricks.push_back(new CombatBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, CombatBrick::Simple));
            }

            actualPosition.x += BRICK_WIDTH;
        }
        actualPosition.x = position.x + BRICK_WIDTH / 2;
        actualPosition.y -= BRICk_HEIGHT;
    }
}

void Map::draw()
{
    glColor3f(0.04f, 0.1f, 0.18f); // цвет фона
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
    for (Brick *brick : combatBricks)
    {
        brick->draw();
    }
    for (Rocket *rocket : rockets)
    {
        rocket->draw();
    }
}

void Map::update() {
    if (isGameOver) return;

    // Проверка условий завершения игры
    if (bricks.empty() && combatBricks.empty()) {
        isGameOver = true;
        return;
    }

    if (platform.getHealth() <= 0) {
        isGameOver = true;
        return;
    }

    // Если шаров нет, перезапускаем шар (если платформа жива)
    if (balls.empty()) {
        platform.hit();
        isThrowBall = false;
        platform.setPosition(PLATFORM_POSITION);

        if (platform.getHealth() > 0) {
            balls.emplace_back(BALL_START_POSITION, platform.getVelocity(), BALL_SIZE);
        } else {
            isGameOver = true;
            return;
        }
    }

    // Обновление платформы и проверка отскока от стен
    platform.update();
    bounceOffWalls();

    // Удаление разрушенных обычных кирпичей
    for (auto it = bricks.begin(); it != bricks.end(); ) {
        if ((*it)->getHealth() <= 0) {
            delete *it;
            it = bricks.erase(it);
        } else {
            ++it;
        }
    }

    // Обновление шаров и проверка столкновени
    for (Ball &ball : balls) {
        if (!isThrowBall) {
            ball.setVelocity(platform.getVelocity());
        } else {
            // Столкновение с платформой
            ball.Collision(platform);

            // Столкновение с обычными кирпичами
            for (Brick *brick : bricks) {
                Velocity oldVel = ball.getVelocity();
                bool collided = ball.Collision(*brick);
                Velocity newVel = ball.getVelocity();

                if (oldVel.x != newVel.x || oldVel.y != newVel.y) {
                    brick->takeDamage(1);
                }
                if (collided) break; // Прерываем после первого столкновения
            }

            // Столкновение с боевыми кирпичами
            for (CombatBrick *brick : combatBricks) {
                Velocity oldVel = ball.getVelocity();
                bool collided = ball.Collision(*brick);
                Velocity newVel = ball.getVelocity();

                if (oldVel.x != newVel.x || oldVel.y != newVel.y) {
                    brick->takeDamage(1);
                    rockets.push_back(new Rocket(brick->getPosition(), ROCKET_SPEED, ROCKET_WIDTH, ROCKET_HEIGHT));
                }
                if (collided) break; // Прерываем после первого столкновения

                // Если боевой кирпич разрушен, создаем ракету
            }
        }

        ball.update();
    }


    // Обновление и проверка ракет
    for (int i = 0; i < rockets.size(); ) {
    rockets[i]->update();
    rockets[i]->setTarget(platform);
    if (rockets[i]->checkCollision(platform)) {
        platform.hit();
        delete rockets[i]; // Удаляем СРАЗУ
        rockets.erase(rockets.begin() + i);
        continue; // Переходим к следующей ракете
    }
    ++i;
}

    // Удаление разрушенных боевых кирпичей
    for (auto it = combatBricks.begin(); it != combatBricks.end(); ) {
        if ((*it)->getHealth() <= 0) {
            delete *it;
            it = combatBricks.erase(it);
        } else {
            ++it;
        }
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
        extraBalls.emplace_back(ball.getPosition(), rotateVelocity(ball.getVelocity(), 2 * M_PI * randomValue / 100), BALL_SIZE);
    }
    balls.insert(balls.end(), extraBalls.begin(), extraBalls.end());
}

void Map::resetMap() {
    isGameOver = false;
    platform = Platform(PLATFORM_POSITION, {0, 0}); // Сброс платформы
    balls.clear(); // Очистка шаров (если хранит объекты)
    isThrowBall = false; // Мяч привязан к платформе

    // Удаление обычных кирпичей
    for (Brick* brick : bricks) {
        if (brick) delete brick;
    }
    bricks.clear();

    // Удаление боевых кирпичей
    for (CombatBrick* brick : combatBricks) {
        if (brick) delete brick;
    }
    combatBricks.clear();

    // Удаление ракет (если вектор хранит указатели)
    for (Rocket* rocket : rockets) {
        if (rocket) delete rocket;
    }
    rockets.clear();

    generateBricks(); // Генерация новой карты
}

// void Map::addRocket(Point position)
// {

// }