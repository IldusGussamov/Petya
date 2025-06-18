#include "GL/freeglut.h"
#include "Game.hpp"
#include <iostream>

void reshape(int width, int height) {
    glViewport(0, 0, width, height); // Устанавливаем вьюпорт на всё окно
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Фиксируем соотношение 4:3, даже если окно изменилось
    float targetAspect = 4.0f / 3.0f;
    float currentAspect = (float)width / (float)height;
    
    if (currentAspect > targetAspect) {
        // Окно шире, чем 4:3 — добавляем чёрные полосы по бокам
        float viewWidth = height * targetAspect;
        float margin = (width - viewWidth) / 2.0f;
        glViewport(margin, 0, viewWidth, height); // Центрируем область отрисовки
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Стандартная проекция
    } else {
        // Окно уже, чем 4:3 — добавляем чёрные полосы сверху/снизу
        float viewHeight = width / targetAspect;
        float margin = (height - viewHeight) / 2.0f;
        glViewport(0, margin, width, viewHeight); // Центрируем область отрисовки
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Стандартная проекция
    }
    
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Petya");
    // glutFullScreen();
    loadTextures();
    glutReshapeFunc(reshape);   

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardDown);
    glutTimerFunc(500 / UPDATES, timerFunc, 0);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}