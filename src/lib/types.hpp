#pragma once

enum class Pattern {
    STRAIGHT,
    DOUBLEBACK,
    WAVE,
    HOLD,
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
        return Pattern::STRAIGHT;
    case EnemyType::WALL:
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return Pattern::HOLD;
    }
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