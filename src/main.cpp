#include "GL/freeglut.h"
#include "Game.hpp"


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Petya");
    // glutFullScreen();
    loadTextures();
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardDown);
    glutTimerFunc(1000 / UPDATES, timerFunc, 0);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}

// main.cpp
// #include <GL/freeglut.h>
// #include "utils.hpp"

// void Display() {
//     glClear(GL_COLOR_BUFFER_BIT);
//     DrawTexturedRectangle(PLATFORM_TEXTURE, {0.0f, 0.0f}, {1.0f, 0.3});
//     glutSwapBuffers();
// }


// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("Textured Rectangle");
//     loadTextures();
//     glutDisplayFunc(Display);
//     glutMainLoop();
    
//     return 0;
// }