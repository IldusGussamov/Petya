#include "Map.hpp"
#include "utils.hpp"
#include "PowerfulBrick.hpp"
#include "SimpleBrick.hpp"
#include "SeriousBrick.hpp"
#include "CombatBrick.hpp"
#include "Rocket.hpp"
#include <GL/freeglut.h>
#include <random>
#include "MagicBrick.hpp"

// Конструктор карты: инициализация платформы, генерация кирпичей и установка направления броска
Map::Map(Point position, Size size) : platform(PLATFORM_POSITION, {0, 0})
{
    this->position = position;
    this->size = size;
    this->generateBricks();
    this->directionThrowBall = 0;
}

// Генерация кирпичей на карте с использованием случайных значений
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
                if (dynamic_cast<CombatBrick*>(bricks.back()))
                    speed *= 0.4;
                bricks.back()->setMovePattern(speed, PLATFORM_WIDTH, dist(gen) % 4);
            }
            actualPosition.x += BRICK_WIDTH;
        }
        actualPosition.x = position.x + BRICK_WIDTH / 2;
        actualPosition.y -= BRICk_HEIGHT;
    }
}

// Отрисовка карты, платформы, кирпичей, шаров, бонусов и ракет
void Map::draw()
{
    // Отрисовка текстурированного фона карты
    DrawTexturedRectangle(MAP_TEXTURE, {position.x + size.width / 2, position.y - size.height / 2}, size);
    platform.draw();

    // Отрисовка направляющей броска мяча, если мяч ещё не брошен
    if (!isThrowBall && !isGameOver)
    {
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(balls[0].getPosition().x, balls[0].getPosition().y, 0);
        glRotatef(directionThrowBall * 180 / M_PI, 0, 0, 1);
        glTranslatef(0, platform.getDimensions().height * 5, 0);
        DrawTexturedRectangle(SCOPE_TEXTURE, {0, 0}, {PLATFORM_WIDTH * 0.25, PLATFORM_WIDTH * 0.25}, -directionThrowBall * 180 / M_PI);
        glEnd();
        glPopMatrix();
    }

    // Отрисовка всех кирпичей
    for (Brick *brick : bricks)
    {
        brick->draw();
    }

    // Отрисовка шаров и направляющей для "липких" шаров
    for (Ball &ball : balls)
    {
        if (ball.getStick() && !isGameOver)
        {
            glColor3f(1, 1, 1);
            glPushMatrix();
            glTranslatef(balls[0].getPosition().x, balls[0].getPosition().y, 0);
            glRotatef(directionThrowBall * 180 / M_PI, 0, 0, 1);
            glTranslatef(0, platform.getDimensions().height * 5, 0);
            DrawTexturedRectangle(SCOPE_TEXTURE, {0, 0}, {PLATFORM_WIDTH * 0.25, PLATFORM_WIDTH * 0.25}, -directionThrowBall * 180 / M_PI);
            glEnd();
            glPopMatrix();
        }
        ball.draw();
    }

    // Отрисовка бонусов
    for (Bonus &bonus : bonuses)
    {
        bonus.draw();
    }

    // Отрисовка ракет
    for (Rocket &rocket : rockets)
    {
        rocket.draw();
    }
}

// Основной игровой цикл: обновление состояния карты, платформы, шаров, кирпичей, бонусов и ракет
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
        directionThrowBall = 0;
        platform.hit();
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

    // Обработка движения и коллизий для движущихся кирпичей
    for (Brick *brick : bricks)
    {
        if (brick->hasPattern())
        {
            // Проверка коллизии с границами карты
            int currentDirection = brick->getCurrentPattern();
            const float eps = std::min(BRICK_WIDTH, BRICk_HEIGHT) * 0.01f;

            // Проверка коллизий с границами
            bool collisionWithMap = false;
            switch (currentDirection)
            {
            case 0: // Вправо
                collisionWithMap = (brick->getRightBorder() + eps >= getRightBorder());
                break;
            case 1: // Влево
                collisionWithMap = (brick->getLeftBorder() - eps <= getLeftBorder());
                break;
            case 2: // Вверх
                collisionWithMap = (brick->getTopBorder() + eps >= getTopBorder());
                break;
            case 3: // Вниз
                collisionWithMap = (brick->getBottomBorder() - eps <= (getButtomBorder() + PLATFORM_ZONE));
                break;
            }
            // Проверка коллизии с другими кирпичами
            bool collisionWithBricks = false;

            if (!collisionWithMap)
            {
                for (Brick *otherBrick : bricks)
                {
                    if (brick == otherBrick || otherBrick->isDestroyed())
                        continue;

                    // Проверяем только кирпичи в направлении движения с учетом eps
                    bool isInDirection = false;
                    switch (currentDirection)
                    {
                    case 0: // Вправо
                        isInDirection = (otherBrick->getLeftBorder() >= brick->getRightBorder() - eps);
                        break;
                    case 1: // Влево
                        isInDirection = (otherBrick->getRightBorder() <= brick->getLeftBorder() + eps);
                        break;
                    case 2: // Вверх
                        isInDirection = (otherBrick->getBottomBorder() >= brick->getTopBorder() - eps);
                        break;
                    case 3: // Вниз
                        isInDirection = (otherBrick->getTopBorder() <= brick->getBottomBorder() + eps);
                        break;
                    }

                    if (isInDirection && brick->checkCollision(*otherBrick))
                    {
                        collisionWithBricks = true;
                        break;
                    }
                }
            }

            // Если есть коллизия, меняем направление движения кирпича
            if (collisionWithMap || collisionWithBricks)
            {
                int newDirection = currentDirection;
                switch (currentDirection)
                {
                case 0: newDirection = 1; break; // Вправо -> Влево
                case 1: newDirection = 0; break; // Влево -> Вправо
                case 2: newDirection = 3; break; // Вверх -> Вниз
                case 3: newDirection = 2; break; // Вниз -> Вверх
                }
                // Вычисляем скорость для смены направления
                float speed = (brick->getVelocity().x != 0) ? fabs(brick->getVelocity().x) : fabs(brick->getVelocity().y);
                brick->setMovePattern(speed, BRICK_WIDTH, newDirection);
            }
        }
        brick->update();
    }

    // Обновление шаров и обработка столкновений с платформой и кирпичами
    for (Ball &ball : balls)
    {
        if (!isThrowBall || ball.getStick())
        {
            ball.setVelocity(platform.getVelocity());
            ball.setMultiplyVelocity(platform.getSpeedMultiplier());
        }
        else
        {
            // Столкновение с платформой и бонусом "липучка"
            if (ball.Collision(platform) and isActivateStickingBonus)
            {
                ball.stick();
                ball.setPosition({platform.getPosition().x, BALL_START_POSITION.y});
                ball.setVelocity({0, 0});
                isActivateStickingBonus = false;
            }

            // Столкновение с кирпичами
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

    // Удаление разрушенных кирпичей и генерация бонусов/ракет
    for (auto it = bricks.begin(); it != bricks.end();)
    {
        if ((*it)->isDestroyed())
        {
            if (dynamic_cast<CombatBrick *>(*it))
            {
                rockets.push_back(Rocket((*it)->getPosition(), ROCKET_WIDTH, ROCKET_HEIGHT));
            }
            if (dynamic_cast<MagicBrick *>(*it))
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

    // Обновление и обработка ракет
    for (int i = 0; i < rockets.size();)
    {
        rockets[i].update();
        rockets[i].setTarget(platform);
        if (rockets[i].checkCollision(platform.shield) && platform.shield.isActivated())
        {
            rockets[i].Collision(platform.shield);
            rockets[i].Bounce();
            platform.shield.deactivate();
            break;
        }
        if (rockets[i].checkCollision(platform))
        {
            platform.hit();
            rockets.erase(rockets.begin() + i);
            break;
        }
        if (rockets[i].getLeftBorder() < getLeftBorder())
        {
            rockets.erase(rockets.begin() + i);
        }
        if (rockets[i].getRightBorder() > getRightBorder())
        {
            rockets.erase(rockets.begin() + i);
        }
        if (rockets[i].getTopBorder() > getTopBorder())
        {
            rockets.erase(rockets.begin() + i);
        }
        if (rockets[i].getBottomBorder() < getButtomBorder())
        {
            rockets.erase(rockets.begin() + i);
        }
        ++i;
    }

    // Обновление и обработка бонусов
    for (int i = 0; i < bonuses.size(); i++)
    {
        bonuses[i].update();
        bonuses[i].Collision(platform);
        if (bonuses[i].isHit)
        {
            // Обработка различных типов бонусов
            if (bonuses[i].getBonusType() == 0) // сброс бонусов
            {
                resetBonuses();
            }
            if (bonuses[i].getBonusType() == 1) // увеличение скорости платформы
            {
                platform.setMultiplyVelocity(2);
            }
            if (bonuses[i].getBonusType() == 2) // увеличение размера платформы
            {
                platform.setSize(PLATFORM_WIDTH * 2, PLATFORM_HEIGHT);
            }
            if (bonuses[i].getBonusType() == 3) // уменьшение размера платформы
            {
                platform.setSize(PLATFORM_WIDTH / 2, PLATFORM_HEIGHT);
            }
            if (bonuses[i].getBonusType() == 4) // увеличение скорости мяча
            {
                for (Ball &ball : balls)
                {
                    ball.setMultiplyVelocity(1.5);
                }
            }
            if (bonuses[i].getBonusType() == 5 || bonuses[i].getBonusType() == 8) // удвоение количества шаров
            {
                addBall();
            }
            if (bonuses[i].getBonusType() == 6) // инверсия платформы
            {
                platform.setMultiplyVelocity(-1);
            }
            if (bonuses[i].getBonusType() == 7 && isThrowCapture) // захват мяча
            {
                isActivateStickingBonus = true;
                isThrowCapture = false;
            }
            if (bonuses[i].getBonusType() == 9) // Щит платформы
            {
                platform.shield.activate();
            }
            bonuses.erase(bonuses.begin() + i);
            i--; // Уменьшаем индекс, чтобы не пропустить следующий бонус
        }
    }
}

// Бросок мяча с платформы
void Map::throwBall()
{
    if (!isCaptureThrown())
    {
        for (Ball &ball : balls)
        {
            if (ball.getStick())
            {
                ball.setVelocity(rotateVelocity({0, BALL_SPEED}, directionThrowBall));
                ball.setMultiplyVelocity(abs(ball.getSpeedMultiplier()));
                ball.setStick(false);
                break;
            }
        }
        isThrowCapture = true;
    }
    this->isThrowBall = true;
    this->balls.front().setVelocity(rotateVelocity({0, BALL_SPEED}, directionThrowBall));
}

// Проверка и обработка отскока шаров от стен карты
void Map::bounceOffWalls()
{
    for (int i = 0; i < balls.size(); ++i)
    {
        Ball &ball = balls[i];
        if (ball.getLeftBorder() <= this->getLeftBorder())
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {1, 0}));

        if (ball.getRightBorder() >= this->getRightBorder())
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {-1, 0}));

        if (ball.getTopBorder() >= this->getTopBorder())
            ball.setVelocity(calculateBounceDirection(ball.getVelocity(), {0, -1}));

        if (ball.getBottomBorder() <= this->getButtomBorder())
            balls.erase(balls.begin() + i);
    }
}

// Получить левую границу карты
Coordinate Map::getLeftBorder()
{
    return position.x;
}

// Получить правую границу карты
Coordinate Map::getRightBorder()
{
    return position.x + size.width;
}

// Получить верхнюю границу карты
Coordinate Map::getTopBorder()
{
    return position.y;
}

// Получить нижнюю границу карты
Coordinate Map::getButtomBorder()
{
    return position.y - size.height;
}

// Проверка, был ли мяч брошен
bool Map::isBallThrown() const
{
    return isThrowBall;
}

// Добавить дополнительный шар (например, при бонусе)
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
        extraBalls.emplace_back(ball.getPosition(), rotateVelocity(ball.getVelocity(), M_PI/4 * randomValue / 100), BALL_SIZE);
        extraBalls.back().setMultiplyVelocity(ball.getSpeedMultiplier());
    }
    balls.insert(balls.end(), extraBalls.begin(), extraBalls.end());
}

// Сбросить карту и все игровые объекты
void Map::resetMap()
{
    isGameOver = false;
    platform = Platform(PLATFORM_POSITION, {0, 0});
    balls.clear();
    bonuses.clear();
    rockets.clear();
    isThrowBall = false;

    // Удаление всех кирпичей
    for (Brick *brick : bricks)
    {
        if (brick)
            delete brick;
    }
    bricks.clear();
    rockets.clear();

    generateBricks();
}

// Сбросить все бонусы и вернуть платформу и мячи к исходным параметрам
void Map::resetBonuses()
{
    platform.setMultiplyVelocity(1);
    platform.setSize(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    platform.shield.deactivate();
    for (Ball &ball : balls)
    {
        ball.setMultiplyVelocity(1);
    }
    // Удаление всех мячей, кроме первого
    while (balls.size() > 1)
    {
        balls.pop_back();
    }
}

// Повернуть направление броска мяча влево
void Map::rotateLeftdirectionThrowBall()
{
    if (directionThrowBall <= MAX_BOUNCE_ANGLE)
        directionThrowBall += M_PI / 80;
}

// Повернуть направление броска мяча вправо
void Map::rotateRightdirectionThrowBall()
{
    if (directionThrowBall >= -MAX_BOUNCE_ANGLE)
        directionThrowBall -= M_PI / 80;
}

// Проверка, был ли выполнен захват мяча
bool Map::isCaptureThrown() const
{
    return isThrowCapture;
}

// Деструктор карты: удаление всех кирпичей
Map::~Map()
{
    for (Brick *brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
}