#include "GL/freeglut.h"
#include "Game.hpp"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Petya");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardDown);
    glutTimerFunc(1000 / FPS, timerFunc, 0);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}