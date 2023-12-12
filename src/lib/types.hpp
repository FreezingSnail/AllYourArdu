#pragma once

enum class Pattern {
    STRAIGHT,
    DOUBLEBACK,
    WAVE,
};

enum class EnemyType {
    HEAD,
    SPIRAL,
    OVAL,
    SMALLSHIP,
    CARRIER,
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
    }
}