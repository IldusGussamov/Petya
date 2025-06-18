#include "Game.hpp"
#include <GL/freeglut.h>
#include <iostream>
#include <chrono>
#include "utils.hpp"

std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now(); // время последнего кадра

bool PRESSED_KEY_A = false; // флаг нажатия клавиши A
bool PRESSED_KEY_D = false; // флаг нажатия клавиши D

Map map(MAP_POSITION, MAP_SIZE);

void renderScene()
{
    auto now = std::chrono::steady_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

    if (deltaTime >= 1000 / FPS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);
        DrawTexturedRectangle(BACKGROUND_TEXTURE, {0, 0}, {2, 2}); // отрисовка фона
        map.draw();

        lastFrameTime = now;
        glutSwapBuffers();
    }
}

void keyboardDown(unsigned char K, int x, int y)
{
    switch (K)
    {
    case 'r':
    case 'R':
    {
        map.resetMap();
        break;
    }
    }
    if (isGameOver)
        return;
    switch (K)
    {
    case ' ':
    {
        if (!map.isBallThrown())
            map.throwBall();
        if(!map.isCaptureThrown())
            map.throwBall();
        break;
    }
    case 'a':
    case 'A':
    {
        PRESSED_KEY_A = true;
        break;
    }
    case 'd':
    case 'D':
    {
        PRESSED_KEY_D = true;
        break;
    }
        if (!map.isBallThrown())
            return;
    case 'q':
    case 'Q':
    {
        map.rotateLeftdirectionThrowBall();
        break;
    }
    case 'e':
    case 'E':
    {
        map.rotateRightdirectionThrowBall();
        break;
    }
    }
}

void timerFunc(int value)
{
    if (PRESSED_KEY_A)
        map.platform.setVelocity({-PLATFORM_SPEED, 0});
    if (PRESSED_KEY_D)
    {
        map.platform.setVelocity({PLATFORM_SPEED, 0});
    }
    if (map.platform.getSpeedMultiplier() < 0)
    {
        if (PRESSED_KEY_D && map.getLeftBorder() >= map.platform.getLeftBorder()) // если управление инвертировано и платформа уперлась в левую стену
        {
            map.platform.resetVelocity();
            std::cout << "D" << std::endl;
        }
        if (PRESSED_KEY_A && map.getRightBorder() <= map.platform.getRightBorder()) // если управление инвертировано и платформа уперлась в правую стену
        {
            map.platform.resetVelocity();
            std::cout << "A" << std::endl;
        }
    }
    if (map.platform.getLeftBorder() <= map.getLeftBorder() && PRESSED_KEY_A && map.platform.getSpeedMultiplier() > 0)
    {
        map.platform.resetVelocity(); // если платформа уперлась в левую стену, останавливаем её
    }
    if (map.platform.getRightBorder() >= map.getRightBorder() && PRESSED_KEY_D && map.platform.getSpeedMultiplier() > 0)
    {
        map.platform.resetVelocity(); // если платформа уперлась в правую стену, останавливаем её
    }
    map.update();
    glutPostRedisplay();
    glutTimerFunc(1000 / UPDATES, timerFunc, 0);
}

void keyboardUp(unsigned char K, int x, int y)
{
    switch (K)
    {
    case 'a':
    case 'A':
    {
        PRESSED_KEY_A = false;
        map.platform.resetVelocity();
        break;
    }
    case 'd':
    case 'D':
    {
        PRESSED_KEY_D = false;
        map.platform.resetVelocity();
        break;
    }
    }
}