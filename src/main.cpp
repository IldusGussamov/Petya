// #include "Platform.hpp"
// #include "GL/freeglut.h"
// #include "ildus.hpp"
// #include "utils.hpp"

// Point position = {0.0, 0.0};
// Velocity velocity = {0.02, 0.010};
// Dimension size = 0.4;

// Object obj(position, velocity, size);

// void renderScene();

// void timerFunc(int value);

// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitWindowPosition(100, 100);
//     glutInitWindowSize(800, 600);
//     glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//     glutCreateWindow("Program");
//     glutDisplayFunc(renderScene);
//     glutTimerFunc(1000 / 60, timerFunc, 0);
//     glutMainLoop();
//     return 0;
// }

// void timerFunc(int value)
// {
//     if (obj.getBorders()[Sides::RIGHT_TOP].x >= 1)
//     {
//         obj.setVelocity(calculateBounceDirection(obj.getVelocity(), {-1, 0}));
//     }
//     if (obj.getBorders()[Sides::RIGHT_TOP].y >= 1)
//     {
//         obj.setVelocity(calculateBounceDirection(obj.getVelocity(), {0, -1}));
//     }
//     if (obj.getBorders()[Sides::LEFT_BOTTOM].x <= -1)
//     {
//         obj.setVelocity(calculateBounceDirection(obj.getVelocity(), {1, 0}));
//     }
//     if (obj.getBorders()[Sides::LEFT_BOTTOM].y <= -1)
//     {
//         obj.setVelocity(calculateBounceDirection(obj.getVelocity(), {0, 1}));
//     }
//     obj.update();
//     glutPostRedisplay();
//     glutTimerFunc(1000 / 60, timerFunc, 0);
// }

// void renderScene()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glPushMatrix();
//     obj.draw();
//     glPopMatrix();
//     glutSwapBuffers();
// }

//тест
