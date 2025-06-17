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
#include "MagicBrick.hpp"

Map::Map(Point position, Size size) : platform(PLATFORM_POSITION, {0, 0})
{
    this->position = position;
    this->size = size;
    this->generateBricks();
    this->directionThrowBall  = 0;
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
            std::uniform_int_distribution<int> dist(1, 120);
            int randomValue = dist(gen);
            if (randomValue < 1)
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
                    bricks.push_back(new CombatBrick(actualPosition, BRICK_WIDTH, BRICk_HEIGHT, 3));
                }
            }
            actualPosition.x += BRICK_WIDTH;
        }
        actualPosition.x = position.x + BRICK_WIDTH / 2;
        actualPosition.y -= BRICk_HEIGHT;
    }
}

void Map::draw()
{
    DrawTexturedRectangle(MAP_TEXTURE, {position.x + size.width/2, position.y - size.height/2}, size); // отрисовка карты
    platform.draw();
    if (!isThrowBall && !isGameOver){
        glPushMatrix();
        glTranslatef(balls[0].getPosition().x, balls[0].getPosition().y, 0);
        glRotatef(directionThrowBall*180/M_PI, 0, 0, 1); // поворот направления броска мяча
        glTranslatef(0, platform.getDimensions().height*5, 0);
        DrawTexturedRectangle(SCOPE_TEXTURE, {0, 0}, {PLATFORM_WIDTH*0.25, PLATFORM_WIDTH*0.25}, -directionThrowBall*180/M_PI);
        glEnd();
        glPopMatrix();
    }
    for (Brick *brick : bricks)
    {
        brick->draw();
    }
    for (Ball &ball : balls)
    {
        if (ball.getStick() && !isGameOver)
        {
        glPushMatrix();
        glTranslatef(balls[0].getPosition().x, balls[0].getPosition().y, 0);
        glRotatef(directionThrowBall*180/M_PI, 0, 0, 1); // поворот направления броска мяча
        glTranslatef(0, platform.getDimensions().height*5, 0);
        DrawTexturedRectangle(SCOPE_TEXTURE, {0, 0}, {PLATFORM_WIDTH*0.25, PLATFORM_WIDTH*0.25}, -directionThrowBall*180/M_PI);
        glEnd();
        glPopMatrix();
        }
        ball.draw();
    }

    for (Bonus &bonus : bonuses)
    {
        bonus.draw();
    }

    for (Rocket &rocket : rockets)
    {
        rocket.draw();
    }
}

void Map::update()
{
    if (isGameOver)
        return;

    // Проверка условий завершения игры
    if (bricks.empty())
    {
        isGameOver = true;
        return;
    }

    if (platform.getHealth() <= 0)
    {
        isGameOver = true;
        return;
    }

    // Если шаров нет, перезапускаем шар (если платформа жива)
    if (balls.empty())
    {
        resetBonuses();
        bonuses.clear();
        rockets.clear();
        directionThrowBall = 0; // сброс направления броска мяча
        platform.hit();
        std::cout << platform.getHealth() << std::endl;
        isThrowBall = false;
        isThrowCapture = true;
        isActivateStickingBonus = false;
        platform.setPosition(PLATFORM_POSITION);

        if (platform.getHealth() > 0)
        {
            balls.emplace_back(BALL_START_POSITION, platform.getVelocity(), BALL_SIZE);
        }
        else
        {
            isGameOver = true;
            return;
        }
    }

    // Обновление платформы и проверка отскока от стен
    platform.update();
    bounceOffWalls();

    // Обновление шаров и проверка столкновени
    for (Ball &ball : balls)
    {
        if (!isThrowBall || ball.getStick())
        {
            ball.setVelocity(platform.getVelocity());
            ball.setMultiplyVelocity(platform.getSpeedMultiplier());
        }
        else
        {
            // Столкновение с платформой
            if (ball.Collision(platform) and isActivateStickingBonus)
            {   
                ball.stick();
                // Если бонус "липучка" активен, мяч прилипает к платформе
                ball.setPosition({platform.getPosition().x, BALL_START_POSITION.y});
                ball.setVelocity({0, 0}); // останавливаем мяч.
                isActivateStickingBonus = false; // деактивируем бонус
            } 
            
            // Столкновение с обычными кирпичами
            for (Brick *brick : bricks)
            {
                Velocity oldVel = ball.getVelocity();
                bool collided = ball.Collision(*brick);
                Velocity newVel = ball.getVelocity();

                if (oldVel.x != newVel.x || oldVel.y != newVel.y)
                {
                    brick->takeDamage(1);
                    break;
                }
            }
        }

        ball.update();
    }

    // Удаление разрушенных обычных кирпичей
    for (auto it = bricks.begin(); it != bricks.end();)
    {
        if ((*it)->isDestroyed())
        {
            if (dynamic_cast<CombatBrick*>(*it))
            {
                rockets.push_back(Rocket((*it)->getPosition(), ROCKET_WIDTH, ROCKET_HEIGHT));
            }
            if(dynamic_cast<MagicBrick*>(*it))
            {
                bonuses.push_back(Bonus((*it)->getPosition(), BONUS_WIDTH, BONUS_HEIGHT));
            }
            delete *it;
            it = bricks.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Обновление и проверка ракет
    for (int i = 0; i < rockets.size();)
    {
        rockets[i].update();
        rockets[i].setTarget(platform);
        if (rockets[i].checkCollision(platform))
        {
            platform.hit();
            std::cout << platform.getHealth() << std::endl;
            rockets.erase(rockets.begin() + i);
            break;
        }
        ++i;
    }

    for (int i = 0; i < bonuses.size(); i++)
    {
        bonuses[i].update();
        bonuses[i].Collision(platform);
        if (bonuses[i].isHit)
        {
            if (bonuses[i].getBonusType() == 0) // сброс бонусов
            {
                resetBonuses();
                std::cout << "Reset bonus" << std::endl;
            }

            if (bonuses[i].getBonusType() == 1) // увеличение скорости платформы
            {
                platform.setMultiplyVelocity(2);
                std::cout << "+speed platform" << std::endl;
            }
            if (bonuses[i].getBonusType() == 2) // увеличение размера платформы
            {
                platform.setSize(PLATFORM_WIDTH * 2, PLATFORM_HEIGHT);
                std::cout << "+size platform" << std::endl;
            }
            if (bonuses[i].getBonusType() == 3) // уменьшение размера платформы
            {
                platform.setSize(PLATFORM_WIDTH / 2, PLATFORM_HEIGHT);
                std::cout << "-size platform" << std::endl;
            }
            if (bonuses[i].getBonusType() == 4) // увеличение скорости мяча
            {
                for (Ball &ball : balls)
                {
                    ball.setMultiplyVelocity(1.5);
                    std::cout << "+speed ball" << std::endl;
                }
            }
            if (bonuses[i].getBonusType() == 5 || bonuses[i].getBonusType() == 8) // удвоение количества шаров
            {
                addBall();
                std::cout << "double ball" << std::endl;
            }
            if (bonuses[i].getBonusType() == 6) // инверсия платформы
            {
                platform.setMultiplyVelocity(-1);
                std::cout << "inverse paltform speed" << std::endl;
            }

            if (bonuses[i].getBonusType() == 7 && isThrowCapture) // захват мяча
            {
                isActivateStickingBonus = true;
                isThrowCapture = false;
                std::cout << "stick" << std::endl;
            }

            // if (bonuses[i].getBonusType() == 9 && isThrowCapture) // Щит платформы
            // {
                // some code ..
            // }

            bonuses.erase(bonuses.begin() + i);
            i--; // Уменьшаем индекс, чтобы не пропустить следующий бонус
        }
    }
}

void Map::throwBall()
{   if (!isCaptureThrown())
    {
        for(Ball &ball : balls)
        {
            if (ball.getStick())
            {
                ball.setVelocity(rotateVelocity({0, BALL_SPEED}, directionThrowBall));
                ball.setStick(false);
                break;
            }
        }
        isThrowCapture = true;
    }
    this->isThrowBall = true;
    this->balls.front().setVelocity(rotateVelocity({0, BALL_SPEED}, directionThrowBall));
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
        if (ball.getStick())
            continue;
        float randomValue = dist(gen);
        extraBalls.emplace_back(ball.getPosition(), rotateVelocity(ball.getVelocity(), 2 * M_PI * randomValue / 100), BALL_SIZE);
        extraBalls.back().setMultiplyVelocity(ball.getSpeedMultiplier());
    }
    balls.insert(balls.end(), extraBalls.begin(), extraBalls.end());
}

void Map::resetMap()
{
    isGameOver = false;
    platform = Platform(PLATFORM_POSITION, {0, 0}); // Сброс платформы
    balls.clear();                                  // Очистка шаров (если хранит объекты)
    bonuses.clear();                                // Очистка бонусов
    rockets.clear();                                // Очистка ракет
    isThrowBall = false;                            // Мяч привязан к платформе

    // Удаление обычных кирпичей
    for (Brick *brick : bricks)
    {
        if (brick)
            delete brick;
    }
    bricks.clear();
    rockets.clear();

    generateBricks(); // Генерация новой карты
}

void Map::resetBonuses()
{
    platform.setMultiplyVelocity(1);
    platform.setSize(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    for (Ball &ball : balls)
    {
        ball.setMultiplyVelocity(1);
    }
    // удаление всех мячей, кроме первого
    while (balls.size() > 1)
    {
        balls.pop_back();
    }; // Очистка бонусов
}

void Map::rotateLeftdirectionThrowBall()
{
    if (directionThrowBall <= MAX_BOUNCE_ANGLE)
        directionThrowBall += M_PI / 80;
}

void Map::rotateRightdirectionThrowBall()
{
    if (directionThrowBall >= -MAX_BOUNCE_ANGLE)
        directionThrowBall -= M_PI / 80; 
}

bool Map::isCaptureThrown() const
{
    return isThrowCapture;
}
