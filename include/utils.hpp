#pragma once
#include <math.h>
#include <GL/freeglut.h>
#include <string>

enum Sides // индексация вершин прямоугольника
{
    LEFT_TOP = 0, // левая верхняя вершина
    RIGHT_TOP,    // правая верхняя вершина
    RIGHT_BOTTOM, // правая нижняя вершина
    LEFT_BOTTOM   // левая нижняя вершина
};

using Coordinate = float; // тип для координат
using Dimension = float;  // тип для размеров
using Angle = float;      // тип для углов
using Health = int;       // тип для здоровья

struct Size // гарабирты
{
    Dimension width;  // ширина
    Dimension height; // высота
};

struct Point // точка
{
    Coordinate x, y; // координаты
};

struct Normal // нормаль
{
    Coordinate x, y; // компоненты вектора нормали к поверхности
};

struct Velocity
{
    Coordinate x, y; // компоненты вектора скорости
};

extern GLuint BALL_TEXTURE; // текстура мяча
extern const char *BALL_TEXTURE_PATH; // путь к текстуре мяча

extern GLuint MAP_TEXTURE; // текстура карты
extern const char *MAP_TEXTURE_PATH; // путь к текстуре карты

extern GLuint BACKGROUND_TEXTURE; // текстура фона
extern const char *BACKGROUND_TEXTURE_PATH; // путь к текстуре фона

extern const char *SIMPLE_BRICK_TEXTURE_PATH; // путь к текстуре простого кирпича
extern GLuint SIMPLE_BRICK_TEXTURE;

extern const char *SERIOUS_BRICK_TEXTURE_PATH; // путь к текстуре серьёзного кирпича
extern GLuint SERIOUS_BRICK_TEXTURE;

extern const char *POWERFUL_BRICK_TEXTURE_PATH; // путь к текстуре мощного кирпича
extern GLuint POWERFUL_BRICK_TEXTURE;

extern const char *COMBAT_BRICK_1_TEXTURE_PATH; // путь к текстуре боевого кирпича 1
extern GLuint COMBAT_BRICK_1_TEXTURE;

extern const char *COMBAT_BRICK_2_TEXTURE_PATH; // путь к текстуре боевого кирпича 2
extern GLuint COMBAT_BRICK_2_TEXTURE;

extern const char *COMBAT_BRICK_3_TEXTURE_PATH; // путь к текстуре боевого кирпича 3
extern GLuint COMBAT_BRICK_3_TEXTURE;

extern const char *MAGIC_BRICK_1_TEXTURE_PATH;  // путь к текстуре магического кирпича 1
extern GLuint MAGIC_BRICK_1_TEXTURE;

extern const char *MAGIC_BRICK_2_TEXTURE_PATH;     // путь к текстуре магического кирпича 2
extern GLuint MAGIC_BRICK_2_TEXTURE;

extern const char *MAGIC_BRICK_3_TEXTURE_PATH;     // путь к текстуре магического кирпича 3
extern GLuint MAGIC_BRICK_3_TEXTURE;

extern const char *BONUS_LARGE_TEXTURE_PATH; // путь к текстуре большого бонуса
extern GLuint BONUS_LARGE_TEXTURE;

extern const char *BONUS_MAGNET_TEXTURE_PATH; // путь к текстуре бонуса магнит
extern GLuint BONUS_MAGNET_TEXTURE; 

extern const char *BONUS_SHIELD_TEXTURE_PATH;  // путь к текстуре бонуса щит
extern GLuint BONUS_SHIELD_TEXTURE; 

extern const char *BONUS_X2_TEXTURE_PATH; // путь к текстуре бонуса x2
extern GLuint BONUS_X2_TEXTURE; 

extern const char *BONUS_ZERO_TEXTURE_PATH; // путь к текстуре бонуса ноль
extern GLuint BONUS_ZERO_TEXTURE; 

extern const char *BONUS_SMALL_TEXTURE_PATH; // путь к текстуре маленького бонуса
extern GLuint BONUS_SMALL_TEXTURE; 

extern const char *BONUS_SWAP_TEXTURE_PATH; // путь к текстуре бонуса своп
extern GLuint BONUS_SWAP_TEXTURE; 

extern const char *ROCKET_TEXTURE_PATH; // путь к текстуре ракеты
extern GLuint ROCKET_TEXTURE; 

extern const char *PLATFORM_0_TEXTURE_PATH; // путь к текстуре платформы 0
extern GLuint PLATFORM_TEXTURE; 

extern const char *PLATFORM_1_TEXTURE_PATH;    // путь к текстуре платформы 1
extern GLuint PLATFORM_1_TEXTURE; 

extern const char *PLATFORM_2_TEXTURE_PATH; // путь к текстуре платформы 2
extern GLuint PLATFORM_2_TEXTURE; 

extern const char *PLATFORM_3_TEXTURE_PATH; // путь к текстуре платформы 3
extern GLuint PLATFORM_3_TEXTURE;

constexpr Dimension WINDOW_WIDTH = 800;                                                                                                // ширина окна
constexpr Dimension WINDOW_HEIGHT = 600;                                                                                                // высота окна
constexpr Size MAP_SIZE{1.25, 1.75};                                                                                                          // размеры карты
constexpr Point MAP_POSITION{-(1-0.375), 0.75};                                                                                                  // позиция карты (левая верхняя вершина)
constexpr Dimension PLATFORM_ZONE = MAP_SIZE.height * 0.4;                                                                              // высота свободной области
constexpr Dimension PLATFORM_WIDTH = 0.2;                                                                                               // ширина платформы
constexpr Dimension PLATFORM_HEIGHT = 0.02*2; 
constexpr Dimension BONUS_WIDTH = 0.25 * PLATFORM_WIDTH;                                                                 // ширина бонуса
constexpr Dimension BONUS_HEIGHT = 0.25 * PLATFORM_WIDTH;                                                                 // высота бонуса 
const unsigned int ROWS = 20;
const unsigned int COLS = 10;    
constexpr Angle ANGLE_THROW_BALL = 0;                                                                                                     // количество рядов и колонок платформы 
constexpr Dimension BRICK_WIDTH = MAP_SIZE.width / COLS;
constexpr Dimension BRICk_HEIGHT = (MAP_SIZE.height - PLATFORM_ZONE) / ROWS;                                                                                          // высота платформы
constexpr Coordinate PLATFORM_SPEED = 0.1 * 0.35 * 0.3/10;                                                                                // скорость платформы
constexpr Point PLATFORM_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, MAP_POSITION.y - MAP_SIZE.height + PLATFORM_ZONE / 5};        // начальная позиция платформы относительно игрового поля
constexpr Angle MAX_BOUNCE_ANGLE = M_PI * 0.4;                                                                                          // максимальный угол отскока мяча от платформы
constexpr Coordinate BALL_SPEED = 0.02 * 0.6/10;
constexpr unsigned int FPS = 60;   
constexpr unsigned int UPDATES = FPS * 10;                                                           // скорость мяча
constexpr Dimension BALL_SIZE = 0.01 * 0.9 * MAP_SIZE.height*1.5;                                                                           // диаметр мяча
constexpr Point BALL_START_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, PLATFORM_POSITION.y + PLATFORM_HEIGHT / 2 + BALL_SIZE / 2 + PLATFORM_HEIGHT*0.1}; // начальные координаты мяча
constexpr Dimension ROCKET_WIDTH = (MAP_SIZE.height - PLATFORM_ZONE) / ROWS;  
constexpr Dimension ROCKET_HEIGHT = MAP_SIZE.width / COLS;  
constexpr Velocity ROCKET_SPEED = {0, -BALL_SPEED * 0.9};  
constexpr Coordinate DROP_SPEED = BALL_SPEED*0.7; // скорость падения бонусов
const Health PLATFORM_HEALTH = 3;
extern bool isGameOver;

// скорость мяча
Velocity calculateBounceDirection(Velocity old_velocty, Normal normal); // вычисление вектора скорости после упругого удара

void drawBorderRectangle(Point *borders);      // рисование прямоугольника по точкам границы
void drawRectangle(Point position, Size size); // рисование прямоугольника по позиции (левая верхняя вершина) и размеру (Ox вправо, а Oy вниз)

template <class T>
T getNorm(T x, T y); // вычисление нормы вектора

Velocity rotateVelocity(Velocity old_velocity, Angle angle); // поворот вектора скорости

Coordinate dot(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // скалярное произведение векторов

Coordinate cross(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // векторное произведение векторов

Velocity calculateBounceDirectonPlatform(Velocity old_velocity, Coordinate difference, Dimension PLATFORM_W = PLATFORM_WIDTH); // вычисление скорости после отскока от платформы

Angle calculateAngleBetweenVectors(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // вычисление угла между векторами

GLuint LoadTexture(const char *path); // загрузка текстуры из файла

void DrawTexturedRectangle(GLuint texture, Point position, Size size); // рисование текстурированного прямоугольника

void loadTextures(); // загрузка текстур