#include "utils.hpp"
#include <math.h>
#include <GL/freeglut.h>

Velocity calculateBounceDirection(Velocity old_velocty, Normal normal)
{
    Velocity new_velocity;

    Dimension norm_old_velocity = getNorm(old_velocty.x, old_velocty.y); // норма старой скорости
    Dimension norm_normal = getNorm(normal.x, normal.y); // норма нормали
    Coordinate dot_old_velocity_and_normal = dot(normal.x, normal.y, old_velocty.x, old_velocty.y); // скалярное произведение нормали и старой скорости
    Angle angleBetweenVectors = acos(dot_old_velocity_and_normal / (norm_normal * norm_old_velocity)); // угол между векторами
    Angle minimalAngleBetweenVectors = angleBetweenVectors > M_PI / 2 ? M_PI - angleBetweenVectors : angleBetweenVectors; // берем наименьший угол между векторами
    Angle rotateAngle = M_PI - 2 * minimalAngleBetweenVectors; // угол на который нужно повернуть старый вектор
    Coordinate crossVectors = cross(normal.x, normal.y, old_velocty.x, old_velocty.y); // определение ориентации
    Angle angle = crossVectors < 0 ? rotateAngle : -rotateAngle; // определение направление поворота
    new_velocity = {cos(angle) * old_velocty.x - sin(angle) * old_velocty.y, sin(angle) * old_velocty.x + cos(angle) * old_velocty.y}; // новый вектор скорости
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
