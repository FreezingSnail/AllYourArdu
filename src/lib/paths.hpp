#pragma once
#include <stdint.h>

struct Path {
    uint16_t stepCount;
    int8_t xMod, yMod;
};

const uint8_t STRAIGHT_STEPS = 1;
const Path STRAIGHT_PATH[] = {{140, 1, 0}};

const uint8_t DOUBLEBACK_STEPS = 2;
const Path DOUBLEBACK_PATH[] = {{80, 1, 0}, {60, -2, 1}};

const uint8_t WAVE_STEPS = 4;
const Path WAVE_PATH[] = {{20, 1, 1}, {40, 1, -1}, {40, 1, 1}, {40, 1, -1}};

const Path WALL_PATH[] = {{45, 1, 0}, {200, 0, 0}, {120, 1, 0}};

const uint8_t BALL_STEPS = 3;
const Path BALL_PATH[] = {{8, 2, 1}, {16, 2, -1}, {16, 2, 1}};

const uint8_t TRI_STEPS = 2;
const Path TRI_PATH[] = {{4, 2, 0}, {1, 2, 1}};