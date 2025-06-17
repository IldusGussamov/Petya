#define STB_IMAGE_IMPLEMENTATION
#include "utils.hpp"
#include <math.h>
#include <GL/freeglut.h>
#include "../include/stb_image.h"

bool isGameOver = false;

const char *BALL_TEXTURE_PATH = "assets/textures/ball.png";
GLuint BALL_TEXTURE = 0;

const char *MAP_TEXTURE_PATH = "assets/textures/map.jpg";
GLuint MAP_TEXTURE = 0;

const char *BACKGROUND_TEXTURE_PATH = "assets/textures/background.png"; 
GLuint BACKGROUND_TEXTURE = 0;

const char *SIMPLE_BRICK_TEXTURE_PATH = "assets/textures/brick1.png";
GLuint SIMPLE_BRICK_TEXTURE = 0;

const char *SERIOUS_BRICK_TEXTURE_PATH = "assets/textures/brick2.png"; 
GLuint SERIOUS_BRICK_TEXTURE = 0;

const char *POWERFUL_BRICK_TEXTURE_PATH = "assets/textures/brick3.png"; 
GLuint POWERFUL_BRICK_TEXTURE = 0;

const char *COMBAT_BRICK_1_TEXTURE_PATH = "assets/textures/combat1.png"; 
GLuint COMBAT_BRICK_1_TEXTURE = 0;

const char *COMBAT_BRICK_2_TEXTURE_PATH = "assets/textures/combat2.png"; 
GLuint COMBAT_BRICK_2_TEXTURE = 0;

const char *COMBAT_BRICK_3_TEXTURE_PATH = "assets/textures/combat3.png"; 
GLuint COMBAT_BRICK_3_TEXTURE = 0;

const char *MAGIC_BRICK_1_TEXTURE_PATH = "assets/textures/magic1.png"; 
GLuint MAGIC_BRICK_1_TEXTURE = 0;

const char *MAGIC_BRICK_2_TEXTURE_PATH = "assets/textures/magic2.png"; 
GLuint MAGIC_BRICK_2_TEXTURE = 0;

const char *MAGIC_BRICK_3_TEXTURE_PATH = "assets/textures/magic3.png"; 
GLuint MAGIC_BRICK_3_TEXTURE = 0;

const char *BONUS_LARGE_TEXTURE_PATH = "assets/textures/magic3.png"; 
GLuint BONUS_LARGE_TEXTURE = 0;

const char *BONUS_MAGNET_TEXTURE_PATH = "assets/textures/bonusMagnet.png";//EWD
GLuint BONUS_MAGNET_TEXTURE = 0; 

const char *BONUS_SHIELD_TEXTURE_PATH = "assets/textures/bonusShield.png";
GLuint BONUS_SHIELD_TEXTURE = 0; 

const char *BONUS_X2_TEXTURE_PATH = "assets/textures/bonusX2.png";
GLuint BONUS_X2_TEXTURE = 0; 

const char *BONUS_ZERO_TEXTURE_PATH = "assets/textures/bonusZero.png";
GLuint BONUS_ZERO_TEXTURE = 0; 

const char *BONUS_SMALL_TEXTURE_PATH = "assets/textures/bonusSmall.png";
GLuint BONUS_SMALL_TEXTURE = 0; 

const char *BONUS_SWAP_TEXTURE_PATH = "assets/textures/bonusSwap.png"; 
GLuint BONUS_SWAP_TEXTURE = 0; 

const char *BONUS_SPEED_TEXTURE_PATH = "assets/textures/bonusSwap.png"; 
GLuint BONUS_SPEED_TEXTURE = 0; 

const char *BONUS_BALL_SPEED_TEXTURE_PATH = "assets/textures/bonusSwap.png"; 
GLuint BONUS_BALL_SPEED_TEXTURE = 0; 

const char *ROCKET_TEXTURE_PATH = "assets/textures/rocket.png"; //asd
GLuint ROCKET_TEXTURE = 0; 

const char *PLATFORM_0_TEXTURE_PATH = "assets/textures/platform0.png"; //asd
GLuint PLATFORM_0_TEXTURE = 0; 

const char *PLATFORM_1_TEXTURE_PATH = "assets/textures/platform1.png"; //asd
GLuint PLATFORM_1_TEXTURE = 0; 

const char *PLATFORM_2_TEXTURE_PATH = "assets/textures/platform2.png"; //asd
GLuint PLATFORM_2_TEXTURE = 0; 

const char *PLATFORM_3_TEXTURE_PATH = "assets/textures/platform3.png"; //asd
GLuint PLATFORM_3_TEXTURE = 0; 

Velocity rotateVelocity(Velocity old_velocity, Angle angle)
{
    Velocity new_velocity = {cos(angle) * old_velocity.x - sin(angle) * old_velocity.y, sin(angle) * old_velocity.x + cos(angle) * old_velocity.y}; // новый вектор скорости
    return new_velocity;
}

Velocity calculateBounceDirectonPlatform(Velocity old_velocity, Coordinate difference, Dimension PLATFOM_W)
{
    Velocity new_velocity{0, getNorm(old_velocity.x, old_velocity.y)};
    Normal normal{0, 1};
    Angle rotateAngle = MAX_BOUNCE_ANGLE * 2 * difference / PLATFOM_W;
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

void drawBorderRectangle(Point *borders)
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
    Dimension norm_one = getNorm(x1, y1);                                 // норма старой скорости
    Dimension norm_two = getNorm(x2, y2);                                 // норма нормали
    Coordinate dotVectors = dot(x1, y1, x2, y2);                          // скалярное произведение нормали и старой скорости
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

GLuint LoadTexture(const char *path)
{
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

    if (!data)
    {
        return 0; // Ошибка загрузки
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
}

void DrawTexturedRectangle(GLuint texture, Point position, Size size, Angle angle)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glRotatef(angle, 0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-size.width/2, size.height/2);
    glTexCoord2f(1, 0); glVertex2f(size.width/2, size.height/2);
    glTexCoord2f(1, 1); glVertex2f(size.width/2, -size.height/2);
    glTexCoord2f(0, 1); glVertex2f(-size.width/2, -size.height/2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void loadTextures()
{
    MAP_TEXTURE = LoadTexture(MAP_TEXTURE_PATH);
    BACKGROUND_TEXTURE = LoadTexture(BACKGROUND_TEXTURE_PATH);
    BALL_TEXTURE = LoadTexture(BALL_TEXTURE_PATH);

    SIMPLE_BRICK_TEXTURE = LoadTexture(SIMPLE_BRICK_TEXTURE_PATH);
    SERIOUS_BRICK_TEXTURE = LoadTexture(SERIOUS_BRICK_TEXTURE_PATH);
    POWERFUL_BRICK_TEXTURE = LoadTexture(POWERFUL_BRICK_TEXTURE_PATH);
    COMBAT_BRICK_1_TEXTURE = LoadTexture(COMBAT_BRICK_1_TEXTURE_PATH);
    COMBAT_BRICK_2_TEXTURE = LoadTexture(COMBAT_BRICK_2_TEXTURE_PATH);
    COMBAT_BRICK_3_TEXTURE = LoadTexture(COMBAT_BRICK_3_TEXTURE_PATH);
    MAGIC_BRICK_1_TEXTURE = LoadTexture(MAGIC_BRICK_1_TEXTURE_PATH);
    MAGIC_BRICK_2_TEXTURE = LoadTexture(MAGIC_BRICK_2_TEXTURE_PATH);
    MAGIC_BRICK_3_TEXTURE = LoadTexture(MAGIC_BRICK_3_TEXTURE_PATH);
    BONUS_LARGE_TEXTURE = LoadTexture(BONUS_LARGE_TEXTURE_PATH);    
    BONUS_MAGNET_TEXTURE = LoadTexture(BONUS_MAGNET_TEXTURE_PATH);  
    BONUS_SHIELD_TEXTURE = LoadTexture(BONUS_SHIELD_TEXTURE_PATH);
    BONUS_X2_TEXTURE = LoadTexture(BONUS_X2_TEXTURE_PATH);
    BONUS_ZERO_TEXTURE = LoadTexture(BONUS_ZERO_TEXTURE_PATH);
    BONUS_SMALL_TEXTURE = LoadTexture(BONUS_SMALL_TEXTURE_PATH);
    BONUS_SWAP_TEXTURE = LoadTexture(BONUS_SWAP_TEXTURE_PATH);
    ROCKET_TEXTURE = LoadTexture(ROCKET_TEXTURE_PATH);
    PLATFORM_0_TEXTURE = LoadTexture(PLATFORM_1_TEXTURE_PATH);
    PLATFORM_1_TEXTURE = LoadTexture(PLATFORM_1_TEXTURE_PATH);
    PLATFORM_2_TEXTURE = LoadTexture(PLATFORM_2_TEXTURE_PATH);
    PLATFORM_3_TEXTURE = LoadTexture(PLATFORM_3_TEXTURE_PATH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Angle getAngle(Coordinate x, Coordinate y)
{
    Angle angle = std::atan2(y, x);  // Диапазон: [-π, π]
    if (angle < 0) {
        angle += 2 * M_PI;  // Преобразуем в [0, 2π)
    }
    return angle;
}