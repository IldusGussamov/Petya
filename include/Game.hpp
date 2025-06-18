#pragma once
#include "Map.hpp"
#include <chrono>
#include "utils.hpp"

extern std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;

extern bool PRESSED_KEY_A;
extern bool PRESSED_KEY_D;

extern Map map;

void renderScene();

void keyboardDown(unsigned char K, int x, int y);

void keyboardUp(unsigned char K, int x, int y);

void timerFunc(int value);



