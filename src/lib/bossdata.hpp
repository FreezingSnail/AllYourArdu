#pragma once
#include "types.hpp"
#include <stdint.h>
#include "../sprites/boss1.h"
#include "../sprites/bossCore.h"

struct BossData {
    const uint8_t *sheet;
    const uint8_t *core;
    BossType type;

    bool vertical;
};

const BossData boss1Data = {boss1, bossCore, BossType::L1, true};