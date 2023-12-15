#pragma once
#include "../sprites/boss1.h"
#include "../sprites/boss2.h"
#include "../sprites/bossCore.h"
#include "types.hpp"
#include <stdint.h>

struct BossData {
    const uint8_t *sheet;
    const uint8_t *core;
    BossType type;

    bool vertical;
};

const BossData boss1Data PROGMEM = {boss1, bossCore, BossType::L5, true};

const BossData boss2Data PROGMEM = {boss2, bossCore, BossType::L1, true};