#pragma once
#include "spawns.hpp"

#define MAX_WAVES 10

struct Wave {
    Spawns const *spawnInstructions;
    uint16_t waitTicks;
    uint8_t x, y;
};

struct Level {
    Wave waves[10];
};

const Level l1 = {
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

const Level DebugL = {{{&WallEnemy, 3000, 130, 21}, {&emptySpawn, 3000, 250, 250}}};

static const Level *levels[] = {
    &DebugL,
};