#include "GL/freeglut.h"
#include "Game.hpp"


// void renderScene();

// void timerFunc(int value);

// void keyfunc(unsigned char K, int x, int y);

// void keyboardUp(unsigned char K, int x, int y);

// void updateScene();

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

// void updateScene()
// {
//     if (PRESSED_KEY_A)
//         map.movePlatformLeft();
//     if (PRESSED_KEY_D)
//         map.movePlatformRight();
//     map.update();
//     glutPostRedisplay();
// }


// void keyboardUp(unsigned char K, int x, int y)
// {
//     if (K == 'a')
//         PRESSED_KEY_A = false;
//     if (K == 'd')
//         PRESSED_KEY_D = false;
//     map.resetVelocity();
// }

// void keyfunc(unsigned char K, int x, int y)
// {
//     if (K == 'd')
//         PRESSED_KEY_D = true;
//     if (K == 'a')
//         PRESSED_KEY_A = true;
// }

// void renderScene()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glPushMatrix();
//     map.draw();
//     glColor3f(1, 1, 1);
//     obj.draw();
//     glPopMatrix();
//     glutSwapBuffers();
// }
