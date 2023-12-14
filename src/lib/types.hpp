#pragma once

enum class Pattern { STRAIGHT, DOUBLEBACK, WAVE, HOLD, BOSS };

enum class EnemyType {
    HEAD,
    SPIRAL,
    OVAL,
    SMALLSHIP,
    CARRIER,
    WALL,
    BROKEN_WALL_TOP,
    BROKEN_WALL_BOTTOM,

    BOSSCORE,
    BOSS_TOP_WING,
    BOSS_BOTTOM_WING,
    BOSS_CORE,

    NONE,
};

enum Formation {
    WIDE,
    // TIGHT,
    TOP,
    BOTTOM,
    FRONT,
    SPIN,
    NONE,
};

enum BossType {
    L1,
};

static Pattern getPatternByType(EnemyType type) {
    switch (type) {
    case EnemyType::HEAD:
        return Pattern::STRAIGHT;
    case EnemyType::SPIRAL:
        return Pattern::WAVE;
    case EnemyType::OVAL:
        return Pattern::DOUBLEBACK;
    case EnemyType::SMALLSHIP:
        return Pattern::WAVE;
    case EnemyType::CARRIER:
    case EnemyType::WALL:
        return Pattern::HOLD;
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return Pattern::STRAIGHT;
    }
    return Pattern::BOSS;
}

static bool hitable(EnemyType type) {
    switch (type) {
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return false;
    default:
        return true;
    }
}