#pragma once

// Подключение необходимых библиотек
#include <math.h>

#include <GL/freeglut.h>

#include <string>

// Перечисление для индексации вершин прямоугольника
enum Sides
{
    LEFT_TOP = 0,    // Левая верхняя вершина

    RIGHT_TOP,       // Правая верхняя вершина

    RIGHT_BOTTOM,    // Правая нижняя вершина

    LEFT_BOTTOM      // Левая нижняя вершина
};

// Псевдонимы типов для улучшения читаемости кода
using Coordinate = float;  // Тип для координат

using Dimension = float;   // Тип для размеров

using Angle = float;       // Тип для углов

using Health = int;        // Тип для здоровья

// Структура для хранения размеров объектов
struct Size
{
    Dimension width;   // Ширина объекта

    Dimension height;  // Высота объекта
};

// Структура для хранения координат точки
struct Point
{
    Coordinate x, y;  // Координаты точки по осям X и Y
};

// Структура для хранения вектора нормали
struct Normal
{
    Coordinate x, y;  // Компоненты вектора нормали к поверхности
};

// Структура для хранения вектора скорости
struct Velocity
{
    Coordinate x, y;  // Компоненты вектора скорости по осям X и Y
};

// Внешние переменные для хранения текстур и путей к ним
extern GLuint BALL_TEXTURE;                 // Текстура мяча

extern const char *BALL_TEXTURE_PATH;       // Путь к текстуре мяча

extern GLuint SHIELD_TEXTURE;               // Текстура щита

extern const char *SHIELD_TEXTURE_PATH;     // Путь к текстуре щита

extern GLuint MAP_TEXTURE;                  // Текстура карты

extern const char *MAP_TEXTURE_PATH;        // Путь к текстуре карты

extern GLuint BACKGROUND_TEXTURE;           // Текстура фона

extern const char *BACKGROUND_TEXTURE_PATH; // Путь к текстуре фона

// Текстуры и пути для различных типов кирпичей
extern const char *SIMPLE_BRICK_TEXTURE_PATH;  // Путь к текстуре простого кирпича

extern GLuint SIMPLE_BRICK_TEXTURE;

extern const char *SERIOUS_BRICK_TEXTURE_PATH; // Путь к текстуре серьёзного кирпича

extern GLuint SERIOUS_BRICK_TEXTURE;

extern const char *POWERFUL_BRICK_TEXTURE_PATH; // Путь к текстуре мощного кирпича

extern GLuint POWERFUL_BRICK_TEXTURE;

extern const char *COMBAT_BRICK_1_TEXTURE_PATH; // Путь к текстуре боевого кирпича 1

extern GLuint COMBAT_BRICK_1_TEXTURE;

extern const char *COMBAT_BRICK_2_TEXTURE_PATH; // Путь к текстуре боевого кирпича 2

extern GLuint COMBAT_BRICK_2_TEXTURE;

extern const char *COMBAT_BRICK_3_TEXTURE_PATH; // Путь к текстуре боевого кирпича 3

extern GLuint COMBAT_BRICK_3_TEXTURE;

extern const char *MAGIC_BRICK_1_TEXTURE_PATH;  // Путь к текстуре магического кирпича 1

extern GLuint MAGIC_BRICK_1_TEXTURE;

extern const char *MAGIC_BRICK_2_TEXTURE_PATH;  // Путь к текстуре магического кирпича 2

extern GLuint MAGIC_BRICK_2_TEXTURE;

extern const char *MAGIC_BRICK_3_TEXTURE_PATH;  // Путь к текстуре магического кирпича 3

extern GLuint MAGIC_BRICK_3_TEXTURE;

// Текстуры и пути для бонусов
extern const char *BONUS_LARGE_TEXTURE_PATH;    // Путь к текстуре большого бонуса

extern GLuint BONUS_LARGE_TEXTURE;

extern const char *BONUS_MAGNET_TEXTURE_PATH;   // Путь к текстуре бонуса магнит

extern GLuint BONUS_MAGNET_TEXTURE; 

extern const char *BONUS_SHIELD_TEXTURE_PATH;   // Путь к текстуре бонуса щит

extern GLuint BONUS_SHIELD_TEXTURE; 

extern const char *BONUS_X2_TEXTURE_PATH;       // Путь к текстуре бонуса x2

extern GLuint BONUS_X2_TEXTURE; 

extern const char *BONUS_ZERO_TEXTURE_PATH;     // Путь к текстуре бонуса ноль

extern GLuint BONUS_ZERO_TEXTURE; 

extern const char *BONUS_SMALL_TEXTURE_PATH;    // Путь к текстуре маленького бонуса

extern GLuint BONUS_SMALL_TEXTURE; 

extern const char *BONUS_SWAP_TEXTURE_PATH;     // Путь к текстуре бонуса своп

extern GLuint BONUS_SWAP_TEXTURE; 

extern const char *BONUS_SPEED_TEXTURE_PATH;    // Путь к текстуре бонуса спид

extern GLuint BONUS_SPEED_TEXTURE; 

extern const char *BONUS_BALL_SPEED_TEXTURE_PATH; // Путь к текстуре бонуса бол спид

extern GLuint BONUS_BALL_SPEED_TEXTURE; 

// Текстуры и пути для других игровых объектов
extern const char *ROCKET_TEXTURE_PATH;         // Путь к текстуре ракеты

extern GLuint ROCKET_TEXTURE; 

extern const char *PLATFORM_0_TEXTURE_PATH;     // Путь к текстуре платформы 0

extern GLuint PLATFORM_0_TEXTURE; 

extern const char *PLATFORM_1_TEXTURE_PATH;     // Путь к текстуре платформы 1

extern GLuint PLATFORM_1_TEXTURE; 

extern const char *PLATFORM_2_TEXTURE_PATH;     // Путь к текстуре платформы 2

extern GLuint PLATFORM_2_TEXTURE; 

extern const char *PLATFORM_3_TEXTURE_PATH;     // Путь к текстуре платформы 3

extern GLuint PLATFORM_3_TEXTURE;

extern const char *SCOPE_TEXTURE_PATH;          // Путь к текстуре прицела

extern GLuint SCOPE_TEXTURE;

// Константы, определяющие параметры игры
constexpr Dimension WINDOW_WIDTH = 800;         // Ширина игрового окна

constexpr Dimension WINDOW_HEIGHT = 600;        // Высота игрового окна

constexpr Size MAP_SIZE{1.25, 1.75};            // Размеры игровой карты

constexpr Point MAP_POSITION{-(1-0.375), 0.75}; // Позиция карты (левая верхняя вершина)

constexpr Dimension PLATFORM_ZONE = MAP_SIZE.height * 0.4; // Высота свободной области

constexpr Dimension PLATFORM_WIDTH = 0.2;       // Ширина платформы

constexpr Dimension PLATFORM_HEIGHT = 0.02*2;   // Высота платформы

constexpr Dimension BONUS_WIDTH = 0.5 * PLATFORM_WIDTH; // Ширина бонуса

constexpr Dimension BONUS_HEIGHT = 0.5 * PLATFORM_WIDTH; // Высота бонуса

const unsigned int ROWS = 20;                   // Количество рядов кирпичей

const unsigned int COLS = 10;                   // Количество колонок кирпичей

constexpr Angle ANGLE_THROW_BALL = 0;           // Угол броска мяча

constexpr Dimension BRICK_WIDTH = MAP_SIZE.width / COLS; // Ширина кирпича

constexpr Dimension BRICk_HEIGHT = (MAP_SIZE.height - PLATFORM_ZONE) / ROWS; // Высота кирпича

constexpr Coordinate PLATFORM_SPEED = 0.1 * 0.35 * 0.3/5 * 1.1; // Скорость движения платформы

constexpr Point PLATFORM_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, MAP_POSITION.y - MAP_SIZE.height + PLATFORM_ZONE / 5}; // Начальная позиция платформы

constexpr Angle MAX_BOUNCE_ANGLE = M_PI * 0.4;  // Максимальный угол отскока мяча от платформы

constexpr Coordinate BALL_SPEED = 0.02 * 0.6/5; // Скорость мяча

constexpr unsigned int FPS = 60;                // Количество кадров в секунду

constexpr unsigned int UPDATES = FPS * 5;       // Частота обновлений

constexpr Dimension BALL_SIZE = 0.01 * 0.9 * MAP_SIZE.height*1.5; // Размер мяча

constexpr Point BALL_START_POSITION = {MAP_POSITION.x + MAP_SIZE.width / 2, PLATFORM_POSITION.y + PLATFORM_HEIGHT / 2 + BALL_SIZE / 2 + PLATFORM_HEIGHT*0.1}; // Начальная позиция мяча

constexpr Dimension ROCKET_WIDTH = (MAP_SIZE.height - PLATFORM_ZONE) / ROWS; // Ширина ракеты

constexpr Dimension ROCKET_HEIGHT = MAP_SIZE.width / COLS; // Высота ракеты

constexpr Velocity ROCKET_SPEED = {0, -BALL_SPEED * 0.9}; // Скорость ракеты

constexpr Coordinate DROP_SPEED = BALL_SPEED*0.7; // Скорость падения бонусов

const Health PLATFORM_HEALTH = 3;               // Здоровье платформы

extern bool isGameOver;                         // Флаг окончания игры

// Прототипы функций
Velocity calculateBounceDirection(Velocity old_velocty, Normal normal); // Вычисление вектора скорости после упругого удара

void drawBorderRectangle(Point *borders);      // Рисование прямоугольника по точкам границы

void drawRectangle(Point position, Size size); // Рисование прямоугольника по позиции и размеру

Dimension getNorm(Coordinate x, Coordinate y); // Вычисление нормы вектора

Velocity rotateVelocity(Velocity old_velocity, Angle angle); // Поворот вектора скорости

Coordinate dot(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // Скалярное произведение векторов

Coordinate cross(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // Векторное произведение векторов

Velocity calculateBounceDirectonPlatform(Velocity old_velocity, Coordinate difference, Dimension PLATFORM_W = PLATFORM_WIDTH); // Вычисление скорости после отскока от платформы

Angle calculateAngleBetweenVectors(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2); // Вычисление угла между векторами

GLuint LoadTexture(const char *path); // Загрузка текстуры из файла

void DrawTexturedRectangle(GLuint texture, Point position, Size size, Angle angle = 0); // Рисование текстурированного прямоугольника

void loadTextures(); // Загрузка всех текстур

Angle getAngle(Coordinate x, Coordinate y); // Получение точного угла от 0 до 2Pi через косинус и синус