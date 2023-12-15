#pragma once
#include "../sprites/boss1.h"
#include "../sprites/bossCore.h"
#include "types.hpp"
#include <stdint.h>

struct BossData {
    const uint8_t *sheet;
    const uint8_t *core;
    BossType type;

    bool vertical;
};

const BossData boss1Data PROGMEM = {boss1, bossCore, BossType::L1, true};