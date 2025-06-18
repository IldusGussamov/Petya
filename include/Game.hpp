#pragma once

// Подключение необходимых заголовочных файлов
#include "Map.hpp"                      // Заголовочный файл для работы с игровой картой

#include <chrono>                       // Библиотека для работы со временем

#include "utils.hpp"                    // Вспомогательные утилиты

// Внешние переменные для управления состоянием игры
extern std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;  // Время последнего кадра для расчета дельты времени

extern bool PRESSED_KEY_A;              // Флаг нажатия клавиши A (движение влево)

extern bool PRESSED_KEY_D;              // Флаг нажатия клавиши D (движение вправо)

extern Map map;                         // Основная игровая карта

// Прототипы функций
void renderScene();                     // Функция отрисовки игровой сцены

// Функции обработки ввода с клавиатуры
void keyboardDown(unsigned char K, int x, int y);  // Обработчик нажатия клавиш

void keyboardUp(unsigned char K, int x, int y);    // Обработчик отпускания клавиш

// Функции игрового процесса
void timerFunc(int value);              // Основная функция игровой логики (вызывается по таймеру)

void reshape(int width, int height);    // Функция обработки изменения размеров окна (сохранение пропорций)

void reshape(int width, int height); // сохранение пропорций игрового окна