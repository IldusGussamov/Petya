#include "Game.hpp"
#include <GL/freeglut.h>
#include <chrono>
#include "utils.hpp"

// Время последнего кадра для контроля FPS
std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();

// Флаги нажатия клавиш управления платформой
bool PRESSED_KEY_A = false; // A — влево
bool PRESSED_KEY_D = false; // D — вправо

// Основная игровая карта
Map map(MAP_POSITION, MAP_SIZE);

// Функция отрисовки сцены
void renderScene()
{
    auto now = std::chrono::steady_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

    // Обновляем только если пришло время нового кадра
    if (deltaTime >= 1000 / FPS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);

        // Отрисовка фона
        DrawTexturedRectangle(BACKGROUND_TEXTURE, {0, 0}, {2, 2});

        // Отрисовка всех игровых объектов
        map.draw();

        lastFrameTime = now;
        glutSwapBuffers();
    }
}

// Обработка нажатия клавиш
void keyboardDown(unsigned char K, int x, int y)
{
    switch (K)
    {
    case 'r':
    case 'R':
        // Сбросить карту (рестарт)
        map.resetMap();
        break;
    }
    if (isGameOver)
        return;
    switch (K)
    {
    case ' ':
        // Бросить мяч (или захват)
        if (!map.isBallThrown())
            map.throwBall();
        if (!map.isCaptureThrown())
            map.throwBall();
        break;
    case 'a':
    case 'A':
        // Включить движение платформы влево
        PRESSED_KEY_A = true;
        break;
    case 'd':
    case 'D':
        // Включить движение платформы вправо
        PRESSED_KEY_D = true;
        break;
        // Следующий блок только если мяч уже брошен
        if (!map.isBallThrown())
            return;
    case 'q':
    case 'Q':
        // Повернуть направление броска влево
        map.rotateLeftdirectionThrowBall();
        break;
    case 'e':
    case 'E':
        // Повернуть направление броска вправо
        map.rotateRightdirectionThrowBall();
        break;
    }
}

// Таймер для обновления состояния игры и движения платформы
void timerFunc(int value)
{
    // Управление платформой по флагам нажатия
    if (PRESSED_KEY_A)
        map.platform.setVelocity({-PLATFORM_SPEED, 0});
    if (PRESSED_KEY_D)
        map.platform.setVelocity({PLATFORM_SPEED, 0});

    // Обработка инвертированного управления
    if (map.platform.getSpeedMultiplier() < 0)
    {
        if (PRESSED_KEY_D && map.getLeftBorder() >= map.platform.getLeftBorder())
        {
            map.platform.resetVelocity();
        }
        if (PRESSED_KEY_A && map.getRightBorder() <= map.platform.getRightBorder())
        {
            map.platform.resetVelocity();
        }
    }

    // Остановка платформы у левой и правой границ
    if (map.platform.getLeftBorder() <= map.getLeftBorder() && PRESSED_KEY_A && map.platform.getSpeedMultiplier() > 0)
    {
        map.platform.resetVelocity();
    }
    if (map.platform.getRightBorder() >= map.getRightBorder() && PRESSED_KEY_D && map.platform.getSpeedMultiplier() > 0)
    {
        map.platform.resetVelocity();
    }

    // Обновление состояния карты (игры)
    map.update();

    // Перерисовка экрана
    glutPostRedisplay();

    // Перезапуск таймера
    glutTimerFunc(1000 / UPDATES, timerFunc, 0);
}

// Обработка отпускания клавиш
void keyboardUp(unsigned char K, int x, int y)
{
    switch (K)
    {
    case 'a':
    case 'A':
        // Остановить движение платформы влево
        PRESSED_KEY_A = false;
        map.platform.resetVelocity();
        break;
    case 'd':
    case 'D':
        // Остановить движение платформы вправо
        PRESSED_KEY_D = false;
        map.platform.resetVelocity();
        break;
    }
}

// Обработка изменения размера окна
void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Фиксируем соотношение 4:3, даже если окно изменилось
    float targetAspect = 4.0f / 3.0f;
    float currentAspect = (float)width / (float)height;

    if (currentAspect > targetAspect) {
        // Окно шире, чем 4:3 — добавляем чёрные полосы по бокам
        float viewWidth = height * targetAspect;
        float margin = (width - viewWidth) / 2.0f;
        glViewport(margin, 0, viewWidth, height);
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    } else {
        // Окно уже, чем 4:3 — добавляем чёрные полосы сверху/снизу
        float viewHeight = width / targetAspect;
        float margin = (height - viewHeight) / 2.0f;
        glViewport(0, margin, width, viewHeight);
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
}