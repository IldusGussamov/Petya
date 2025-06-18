// Подключение библиотеки GLUT для работы с графикой и окнами
#include "GL/freeglut.h"
// Подключение заголовка с логикой игры
#include "Game.hpp"

int main(int argc, char **argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);

    // Установка позиции окна (левый верхний угол экрана)
    glutInitWindowPosition(0, 0);

    // Установка размера окна
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Установка режима отображения: RGBA, глубина, двойная буферизация
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    // Создание окна с заголовком "Petya"
    glutCreateWindow("Petya");

    // Загрузка текстур
    loadTextures();

    // Установка функции обработки изменения размера окна
    glutReshapeFunc(reshape);

    // Установка функции отрисовки сцены
    glutDisplayFunc(renderScene);

    // Установка функции обработки нажатия клавиш
    glutKeyboardFunc(keyboardDown);

    // Установка таймера для обновления игры
    glutTimerFunc(500 / UPDATES, timerFunc, 0);

    // Установка функции обработки отпускания клавиш
    glutKeyboardUpFunc(keyboardUp);

    // Запуск основного цикла GLUT
    glutMainLoop();

    // Завершение программы
    return 0;
}