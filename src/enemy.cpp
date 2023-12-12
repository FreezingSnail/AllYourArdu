#include "enemy.hpp"
#include "globals.hpp"
#include "sprites/headEnemy.h"

void Enemy::draw() {
    switch (type) {
    case EnemyType::HEAD:
        Sprites::drawSelfMasked(x, y, headEnemy, 0);
        // getBounding().draw();
        break;
    }
}

void Enemy::tick() {
    if (!active) {
        return;
    }
    ticker++;
    switch (pattern) {
    case Pattern::STRAIGHT:
        if (ticker % 16) {
            x--;
        }
        break;
    }

    if (x < 0) {
        active = false;
    }
    draw();
}

void Enemy::spawn(uint8_t y) {
    this->y = y;
    x = 130;
    active = true;
}

void Enemy::despawn() {
    active = false;
}

BoundBox Enemy::getBounding() {
    switch (type) {
    case EnemyType::HEAD:
        return BoundBox(x + 4, y, 12, 16);
        break;
    }
}

bool Enemy::hit(BoundBox bulletBox) {
    return getBounding().overlap(bulletBox);
}

void Enemy::reset() {
    x = 160;
    active = false;
}