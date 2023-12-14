#include "enemy.hpp"
#include "globals.hpp"
#include "lib/paths.hpp"
#include "sprites/carrierEnemy.h"
#include "sprites/enemieShips.h"
#include "sprites/gateEnemy.h"
#include "sprites/headEnemy.h"

static int16_t getHitPoints(EnemyType type) {
    switch (type) {
    case EnemyType::HEAD:
        return 15;
    case EnemyType::SPIRAL:
        return 5;
    case EnemyType::OVAL:
        return 1;
    case EnemyType::SMALLSHIP:
        return 10;
    case EnemyType::CARRIER:
        return 40;
    case EnemyType::WALL:
        return 200;

    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return -1;
    }
}

static int16_t getSubMod(EnemyType type) {
    switch (type) {
    case EnemyType::HEAD:
    case EnemyType::SPIRAL:
    case EnemyType::OVAL:
    case EnemyType::SMALLSHIP:
        return 1;
    case EnemyType::CARRIER:
    case EnemyType::WALL:
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BROKEN_WALL_TOP:
        return 4;
    }
}

bool Enemy::shoot() {
    switch (type) {
    case EnemyType::HEAD:
    case EnemyType::CARRIER:
        return true;
    }
    return false;
}

void Enemy::blink() {
    switch (type) {
    case EnemyType::HEAD:
        Sprites::drawErase(x, y, headEnemy, 0);
        break;

    case EnemyType::SPIRAL:
        Sprites::drawErase(x, y, enemieShips, 0 + (3 * frame));
        break;

    case EnemyType::OVAL:
        Sprites::drawErase(x, y, enemieShips, 1 + (3 * frame));
        break;

    case EnemyType::SMALLSHIP:
        Sprites::drawErase(x, y, enemieShips, 2 + (3 * frame));
        break;

    case EnemyType::CARRIER:
        Sprites::drawErase(x, y, carrierEnemy, frame / 2);
        break;
    case EnemyType::WALL:
        Sprites::drawErase(x, y, gateEnemy, 1);
    }
}

void Enemy::draw() {
    // getBounding().draw();
    switch (type) {
    case EnemyType::HEAD:
        Sprites::drawSelfMasked(x, y, headEnemy, 0);
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
    case EnemyType::WALL:
        Sprites::drawSelfMasked(x, y, gateEnemy, 1);
        Sprites::drawSelfMasked(x, y + 23, gateEnemy, 2);
        Sprites::drawSelfMasked(x, y - 24, gateEnemy, 0);
        break;
    case EnemyType::BROKEN_WALL_TOP:
        Sprites::drawSelfMasked(x, y, gateEnemy, 0);
        break;
    case EnemyType::BROKEN_WALL_BOTTOM:
        Sprites::drawSelfMasked(x, y, gateEnemy, 2);
        break;
    }
}

void Enemy::applyPath(Path p) {

    subx -= p.xMod;
    suby -= p.yMod;

    if (suby < 0) {
        suby = 0;
    }
    if (subx < 0) {
        subx = 0;
    }
    if (subx >= ((128 * SUBPIXELMOD) - (16 * SUBPIXELMOD))) {
        subx = ((128 * SUBPIXELMOD) - (16 * SUBPIXELMOD));
    }
    if (suby >= ((64 * SUBPIXELMOD) - (16 * SUBPIXELMOD))) {
        suby = ((64 * SUBPIXELMOD) - (16 * SUBPIXELMOD));
    }

    x = subx / SUBPIXELMOD;
    y = suby / SUBPIXELMOD;
    if (subx % SUBPIXELMOD == 0) {
        stepCount++;
    }
}

void Enemy::tick(Bullet *enemyBullets) {
    if (!active) {
        return;
    }

    ticker++;
    if (ticker % 15 == 0) {
        frame++;
        if (frame > 3) {
            frame = 0;
        }
    }

    if (shoot()) {
        bullet(enemyBullets);
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
    case Pattern::HOLD:
        if (stepCount > WALL_PATH[stepPointer].stepCount) {
            stepCount = 0;
            stepPointer++;
        }
        applyPath(WALL_PATH[stepPointer]);
    }

    if (x < 0) {
        active = false;
    }
    draw();
}

void Enemy::spawn(EnemyType type, int16_t x, int16_t y) {
    this->y = y;
    this->x = x;
    active = true;
    stepCount = 0;
    stepPointer = 0;
    pattern = getPatternByType(type);
    this->type = type;
    hitCounter = getHitPoints(type);
    SUBPIXELMOD = getSubMod(type);
    subx = x * SUBPIXELMOD;
    suby = y * SUBPIXELMOD;
}
void Enemy::spawnBrokenWall(EnemyType type, int16_t x, int16_t y, uint8_t stepCounter, uint8_t stepPointer) {
    spawn(type, x, y);
    this->stepCount = stepCounter;
    this->stepPointer = stepPointer;
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
        return BoundBox(x + 12, y + 10, 18, 20);
    case EnemyType::WALL:
        return BoundBox(x, 0, 36, 64);
    case EnemyType::BROKEN_WALL_BOTTOM:
        return BoundBox(x, y, 30, 20);
    case EnemyType::BROKEN_WALL_TOP:
        return BoundBox(x, 0, 30, 22);
    }
}

BoundBox Enemy::getCollision() {
    switch (type) {
    case EnemyType::WALL:
        return BoundBox(x, 0, 63, 128);
    default:
        return getBounding();
    }
}

bool Enemy::hit(BoundBox bulletBox) {
    return getBounding().overlap(bulletBox);
}

bool Enemy::takeDamage(uint8_t damage) {
    blink();
    hitCounter -= damage;
    if (hitCounter == 0) {
        reset();
        return true;
    }
    return false;
}

void Enemy::reset() {
    // x = 160;
    active = false;
}

void Enemy::bullet(Bullet *enemyBullets) {
    uint8_t xS, yS, t, tickerMod;
    switch (this->type) {
    case EnemyType::CARRIER:
        xS = this->x + 10;
        yS = this->y + 25;
        t = 2;
        tickerMod = 40;
        break;
    default:
        xS = this->x;
        yS = this->y;
        t = 1;
        tickerMod = 20;
    }

    if (ticker % tickerMod == 0) {
        for (uint8_t i = 0; i < BULLETCOUNT; i++) {
            if (!enemyBullets[i].active) {
                enemyBullets[i].start(xS, yS, 2, 1, 0, true);
                return;
            }
        }
    }
}