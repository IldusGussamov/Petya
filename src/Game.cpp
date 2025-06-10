#include "Game.hpp"
#include <GL/freeglut.h>
#include <iostream>

bool PRESSED_KEY_A = false; // флаг нажатия клавиши A
bool PRESSED_KEY_D = false; // флаг нажатия клавиши D

Map map(MAP_POSITION, MAP_SIZE);

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    map.draw();
    glutSwapBuffers();
}

void keyboardDown(unsigned char K, int x, int y)
{
    switch (K)
    {
    case ' ':
    {
        if (!map.isBallThrown())
            map.throwBall();
        break;
    }
    case 'a':
    {
        PRESSED_KEY_A = true;
        break;
    }
    case 'd':
    {
        PRESSED_KEY_D = true;
        break;
    }
    }
}

void timerFunc(int value)
{
    if (PRESSED_KEY_A)
        map.platform.setVelocity({-PLATFORM_SPEED, 0});
    if (PRESSED_KEY_D)
        map.platform.setVelocity({PLATFORM_SPEED, 0});
    map.update();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerFunc, 0);
}

void keyboardUp(unsigned char K, int x, int y)
{
    switch (K)
    {
    case 'a':
    {
        PRESSED_KEY_A = false;
        map.platform.resetVelocity();
        break;
    }
    case 'd':
    {
        PRESSED_KEY_D = false;
        map.platform.resetVelocity();
        break;
    }
    }
}