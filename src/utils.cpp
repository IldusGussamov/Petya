#include "utils.hpp"
#include <math.h>
#include <GL/freeglut.h>

// bool PRESSED_KEY_A = false;
// bool PRESSED_KEY_D = false;

Velocity rotateVelocity(Velocity old_velocity, Angle angle)
{
    Velocity new_velocity = {cos(angle) * old_velocity.x - sin(angle) * old_velocity.y, sin(angle) * old_velocity.x + cos(angle) * old_velocity.y}; // новый вектор скорости
    return new_velocity;
}

Velocity calculateBounceDirectonPlatform(Velocity old_velocity, Coordinate difference, Dimension PLATFOM_W)
{
    Velocity new_velocity{0, getNorm(old_velocity.x, old_velocity.y)};
    Normal normal{0, 1};
    Angle rotateAngle =  MAX_BOUNCE_ANGLE * 2 * difference/PLATFOM_W;
    return rotateVelocity(new_velocity, rotateAngle);
}

Velocity calculateBounceDirection(Velocity old_velocity, Normal normal)
{
    Velocity new_velocity;
    Angle angleBetweenVectors = calculateAngleBetweenVectors(old_velocity.x, old_velocity.y, normal.x, normal.y);         // угол между векторами
    Angle minimalAngleBetweenVectors = angleBetweenVectors > M_PI / 2 ? M_PI - angleBetweenVectors : angleBetweenVectors; // берем наименьший угол между векторами
    Angle rotateAngle = M_PI - 2 * minimalAngleBetweenVectors;                                                            // угол на который нужно повернуть старый вектор
    Coordinate crossVectors = cross(normal.x, normal.y, old_velocity.x, old_velocity.y);                                  // определение ориентации
    Angle angle = crossVectors < 0 ? rotateAngle : -rotateAngle;                                                          // определение направления поворота
    new_velocity = rotateVelocity(old_velocity, angle);                                                                   // новый вектор
    return new_velocity;
}

void drawRectangle(Point *borders)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2f(borders[Sides::LEFT_TOP].x, borders[Sides::LEFT_TOP].y);
    glVertex2f(borders[Sides::RIGHT_TOP].x, borders[Sides::RIGHT_TOP].y);
    glVertex2f(borders[Sides::RIGHT_BOTTOM].x, borders[Sides::RIGHT_BOTTOM].y);
    glVertex2f(borders[Sides::LEFT_BOTTOM].x, borders[Sides::LEFT_BOTTOM].y);
    glEnd();
    glPopMatrix();
}

template <class T>
T getNorm(T x, T y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

Coordinate dot(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
{
    return x1 * x2 + y1 * y2;
}

Coordinate cross(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
{
    return x1 * y2 - y1 * x2;
}

Angle calculateAngleBetweenVectors(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
{
    Dimension norm_one = getNorm(x1, y1);        // норма старой скорости
    Dimension norm_two = getNorm(x2, y2);        // норма нормали
    Coordinate dotVectors = dot(x1, y1, x2, y2); // скалярное произведение нормали и старой скорости
    Angle angleBetweenVectors = acos(dotVectors / (norm_one * norm_two)); // угол между двумя векторами
    return angleBetweenVectors;
}

void drawRectangle(Point position, Size size)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2d(position.x, position.y);
    glVertex2d(position.x + size.width, position.y);
    glVertex2d(position.x + size.width, position.y - size.height);
    glVertex2d(position.x, position.y - size.height);
    glEnd();
    glPopMatrix();
}
