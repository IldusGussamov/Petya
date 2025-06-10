#include "GL/freeglut.h"
#include "Game.hpp"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 400);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Program");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardDown);
    glutTimerFunc(1000 / 60, timerFunc, 0);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}