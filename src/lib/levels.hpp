#pragma once
#include "spawns.hpp"
#include "Arduboy2.h"

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
    {{&lineSpiral, 300, 130, 30},
     {&Ovals, 300, 130, 30},
     {&SmallShips, 300, 130, 30},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250},
     {&emptySpawn, 0, 250, 250}},
};

const Level DebugL PROGMEM = {{{&Carrier, 3000, 128, 15},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250},
                               {&emptySpawn, 0, 250, 250}}};

const Level *const levels[] PROGMEM = {
    &DebugL,
    //&l1,
};

template <typename T> T *pgm_read_pointer(T *const *pointer) {
    return reinterpret_cast<T *>(pgm_read_ptr(pointer));
}
