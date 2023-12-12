#include "enemy.hpp"
#include "globals.hpp"
#include "lib/paths.hpp"
#include "sprites/carrierEnemy.h"
#include "sprites/enemieShips.h"
#include "sprites/headEnemy.h"

void Enemy::draw() {
    switch (type) {
    case EnemyType::HEAD:
        Sprites::drawSelfMasked(x, y, headEnemy, 0);
        // getBounding().draw();
        break;

    case EnemyType::SPIRAL:
        Sprites::drawSelfMasked(x, y, enemieShips, 0 + (3 * frame));
        break;

    case EnemyType::OVAL:
        Sprites::drawSelfMasked(x, y, enemieShips, 1 + (3 * frame));
        break;

    case EnemyType::SMALLSHIP:
        Sprites::drawSelfMasked(x, y, enemieShips, 2 + (3 * frame));
        break;

    case EnemyType::CARRIER:
        Sprites::drawSelfMasked(x, y, carrierEnemy, frame / 2);
        break;
    }
}

void Enemy::applyPath(Path p) {
    x -= p.xMod;
    y -= p.yMod;
}

void Enemy::tick() {
    if (!active) {
        return;
    }

    ticker++;
    stepCount++;
    if (ticker % 15 == 0) {
        frame++;
        if (frame > 3) {
            frame = 0;
        }
    }

    switch (pattern) {
    case Pattern::STRAIGHT:
        applyPath(STRAIGHT_PATH[0]);
        break;

    case Pattern::DOUBLEBACK:
        if (stepCount > DOUBLEBACK_PATH[stepPointer].stepCount) {
            stepCount = 0;
            stepPointer++;
        }
        applyPath(DOUBLEBACK_PATH[stepPointer]);
        break;

    case Pattern::WAVE:
        if (stepCount > WAVE_PATH[stepPointer].stepCount) {
            stepCount = 0;
            stepPointer++;
        }
        applyPath(WAVE_PATH[stepPointer]);
        break;
    }

    if (x < 0) {
        active = false;
    }
    draw();
}

void Enemy::spawn(EnemyType type, uint8_t x, uint8_t y) {
    this->y = y;
    this->x = x;
    active = true;
    stepCount = 0;
    stepPointer = 0;
    pattern = getPatternByType(type);
    this->type = type;
}

void Enemy::despawn() {
    active = false;
}

BoundBox Enemy::getBounding() {
    switch (type) {
    case EnemyType::HEAD:
        return BoundBox(x + 4, y, 12, 16);
    case EnemyType::SPIRAL:
        return BoundBox(x, y, 8, 8);

    case EnemyType::OVAL:
        return BoundBox(x + 1, y, 6, 8);

    case EnemyType::SMALLSHIP:
        return BoundBox(x + 2, y, 4, 8);

    case EnemyType::CARRIER:
        return BoundBox(x + 12, y + 10, 24, 20);
    }
}

bool Enemy::hit(BoundBox bulletBox) {
    return getBounding().overlap(bulletBox);
}

void Enemy::reset() {
    x = 160;
    active = false;
}