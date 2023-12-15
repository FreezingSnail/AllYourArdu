#pragma once

enum class Pattern {
    STRAIGHT,
    DOUBLEBACK,
    WAVE,
    HOLD,
    BOSS,
    BOSSLONG,
};

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
    BOSSCORELONG,
    BOSS_TOP_WING,
    BOSS_BOTTOM_WING,
    BOSS_CORE,

    BOSS_FRONT,
    BOSS_MIDDLE,
    BOSS_BACK,

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
    L5,
    L1,
};

static Pattern getPatternByType(EnemyType type) {
    switch (type) {
    case EnemyType::HEAD:
    case EnemyType::CARRIER:
        return Pattern::STRAIGHT;
    case EnemyType::SPIRAL:
        return Pattern::WAVE;
    case EnemyType::OVAL:
        return Pattern::DOUBLEBACK;
    case EnemyType::SMALLSHIP:
        return Pattern::WAVE;
    case EnemyType::WALL:
        return Pattern::HOLD;
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return Pattern::STRAIGHT;
    case EnemyType::BOSS_FRONT:
    case EnemyType::BOSS_MIDDLE:
    case EnemyType::BOSS_BACK:
    case EnemyType::BOSSCORELONG:
        return Pattern::BOSSLONG;
    }
    return Pattern::BOSSLONG;
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