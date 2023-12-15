#pragma once;
#include "types.hpp"
#include <stdint.h>

struct Spawns {
    EnemyType type;
    uint8_t count;
    uint8_t tickInterval;
};

const Spawns emptySpawn PROGMEM = {EnemyType::NONE, 0, 0};

const Spawns lineSpiral PROGMEM = {EnemyType::SPIRAL, 15, 15};

const Spawns Ovals PROGMEM = {EnemyType::OVAL, 6, 15};

const Spawns SmallShips PROGMEM = {EnemyType::SMALLSHIP, 6, 15};

const Spawns Carrier PROGMEM = {EnemyType::CARRIER, 1, 1};

const Spawns WallEnemy PROGMEM = {EnemyType::WALL, 1, 1};

const Spawns Boss PROGMEM = {EnemyType::BOSS_CORE, 1, 1};

const Spawns BossLong PROGMEM = {EnemyType::BOSSCORELONG, 1, 1};