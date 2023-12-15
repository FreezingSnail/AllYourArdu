#pragma once
#include "Arduboy2.h"
#include "spawns.hpp"

#define MAX_WAVES 10

struct Wave {
    Spawns const *spawnInstructions;
    uint16_t waitTicks;
    uint8_t x, y;
};

struct Level {
    const Wave waves[11];
};

const Level l1 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 30},
        {&Ovals, 240, 130, 30},
        {&Ovals, 240, 130, 20},
        {&Ovals, 240, 130, 40},
        {&lineSpiral, 500, 130, 30},
        {&emptySpawn, 0, 250, 250},
        {&Ovals, 240, 130, 20},
        {&Ovals, 240, 130, 40},
        {&lineSpiral, 500, 130, 30},
        {&emptySpawn, 0, 250, 250},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l2 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 30},
        {&Ovals, 240, 130, 20},
        {&Ovals, 240, 130, 40},
        {&SmallShips, 500, 130, 25},
        {&lineSpiral, 500, 130, 30},
        {&Carrier, 500, 130, 12},
        {&Ovals, 240, 130, 20},
        {&SmallShips, 500, 130, 30},
        {&SmallShips, 500, 130, 35},
        {&emptySpawn, 0, 250, 250},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l3 PROGMEM = {
    {
        {&SmallShips, 500, 130, 30},
        {&Ovals, 240, 130, 40},
        {&SmallShips, 500, 130, 20},
        {&Carrier, 500, 130, 12},
        {&lineSpiral, 500, 130, 35},
        {&Ovals, 240, 130, 28},
        {&Ovals, 240, 130, 22},
        {&SmallShips, 500, 130, 37},
        {&Carrier, 500, 130, 12},
        {&Carrier, 500, 130, 27},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l4 PROGMEM = {
    {
        {&Carrier, 500, 130, 12},
        {&Ovals, 240, 130, 22},
        {&Carrier, 500, 130, 32},
        {&WallEnemy, 1000, 130, 21},
        {&lineSpiral, 500, 130, 32},
        {&SmallShips, 500, 130, 45},
        {&Ovals, 240, 130, 21},
        {&Carrier, 500, 130, 10},
        {&Carrier, 500, 130, 20},
        {&SmallShips, 500, 130, 33},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l5 PROGMEM = {
    {
        {&Carrier, 500, 130, 12},
        {&Ovals, 240, 130, 40},
        {&lineSpiral, 500, 130, 36},
        {&SmallShips, 500, 130, 25},
        {&lineSpiral, 500, 130, 44},
        {&Ovals, 500, 130, 31},
        {&SmallShips, 500, 130, 30},
        {&WallEnemy, 1000, 130, 21},
        {&Carrier, 500, 130, 15},
        {&BossLong, 3000, 128, 15},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l6 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 15},
        {&SmallShips, 500, 130, 30},
        {&WallEnemy, 1000, 130, 21},
        {&SmallShips, 500, 130, 17},
        {&lineSpiral, 500, 130, 22},
        {&SmallShips, 500, 130, 35},
        {&WallEnemy, 1000, 130, 21},
        {&Ovals, 240, 130, 40},
        {&Carrier, 500, 130, 12},
        {&lineSpiral, 500, 130, 15},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l7 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 32},
        {&WallEnemy, 1000, 130, 21},
        {&Ovals, 240, 130, 19},
        {&Ovals, 240, 130, 42},
        {&lineSpiral, 500, 130, 10},
        {&SmallShips, 500, 130, 35},
        {&Ovals, 240, 130, 21},
        {&SmallShips, 500, 130, 22},
        {&WallEnemy, 1000, 130, 21},
        {&Ovals, 240, 130, 19},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l8 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 30},
        {&Carrier, 500, 130, 15},
        {&WallEnemy, 1000, 130, 21},
        {&SmallShips, 500, 130, 30},
        {&lineSpiral, 500, 130, 30},
        {&SmallShips, 500, 130, 30},
        {&WallEnemy, 1000, 130, 21},
        {&Ovals, 240, 130, 40},
        {&Carrier, 500, 130, 12},
        {&WallEnemy, 1000, 130, 21},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l9 PROGMEM = {
    {
        {&WallEnemy, 1000, 130, 21},
        {&Ovals, 240, 130, 30},
        {&SmallShips, 500, 130, 35},
        {&Ovals, 240, 130, 40},
        {&lineSpiral, 500, 130, 35},
        {&SmallShips, 500, 130, 35},
        {&Carrier, 500, 130, 15},
        {&SmallShips, 500, 130, 35},
        {&Carrier, 500, 130, 12},
        {&SmallShips, 500, 130, 35},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level l10 PROGMEM = {
    {
        {&lineSpiral, 500, 130, 30},
        {&Ovals, 500, 130, 30},
        {&SmallShips, 500, 130, 30},
        {&Carrier, 500, 130, 12},
        {&Carrier, 500, 130, 15},
        {&SmallShips, 500, 130, 30},
        {&SmallShips, 500, 130, 30},
        {&WallEnemy, 1000, 130, 21},
        {&Carrier, 500, 130, 15},
        {&Boss, 3000, 128, 15},
        {&emptySpawn, 0, 250, 250},
    },
};

const Level *const levels[] PROGMEM = {
    //&DebugL,
    &l1, &l2, &l3, &l4, &l5, &l6, &l7, &l8, &l9, &l10};

template <typename T> T *pgm_read_pointer(T *const *pointer) {
    return reinterpret_cast<T *>(pgm_read_ptr(pointer));
}
