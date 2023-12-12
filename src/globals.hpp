#pragma once
#include "bullet.hpp"

#define dbf __attribute__((optimize("-O0")))

#define BULLETCOUNT 20
#define ENEMIES 20

enum class ShipType {
    MINI,
    ROD,
    EYE,
    BOMB,
    NONE,
};
