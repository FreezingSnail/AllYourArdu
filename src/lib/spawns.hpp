#pragma once;
#include "types.hpp"
#include <stdint.h>

struct Spawns {
    EnemyType type;
    uint8_t count;
    uint8_t tickInterval;
};

const Spawns emptySpawn{EnemyType::NONE, 0, 0};

const Spawns lineSpiral = {EnemyType::SPIRAL, 15, 15};

const Spawns Ovals = {EnemyType::OVAL, 6, 15};

const Spawns SmallShips = {EnemyType::SMALLSHIP, 6, 15};

const Spawns Carrier = {EnemyType::CARRIER, 1, 1};

const Spawns WallEnemy = {EnemyType::WALL, 1, 1};