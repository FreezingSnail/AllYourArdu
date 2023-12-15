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
    const Wave waves[10];
};

const Level l1 PROGMEM = {
    {{&lineSpiral, 500, 130, 30},
     {&Ovals, 500, 130, 30},
     {&SmallShips, 500, 130, 30},
     {&WallEnemy, 1000, 130, 21},
     {&Carrier, 500, 130, 30},
     {&Boss, 3000, 128, 15},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250}},
};

const Level DebugL PROGMEM = {{{&Boss, 3000, 128, 15},   //{&WallEnemy, 1000, 130, 21},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250}}};

const Level *const levels[] PROGMEM = {
    //&DebugL,
    &l1,
};

template <typename T> T *pgm_read_pointer(T *const *pointer) {
    return reinterpret_cast<T *>(pgm_read_ptr(pointer));
}
