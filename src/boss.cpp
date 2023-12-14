#include "boss.hpp"
#include "lib/bossdata.hpp"
#include "globals.hpp"

void BossEnemy::load(BossData *const data) {
    x = 128;
    y = 24;
    coreSprite = data->core;
    bodySheet = data->sheet;
    type = data->type;
    vertical = data->vertical;
    active = true;
    switch (type) {
    case BossType::L1:
        enemies[0].spawn(EnemyType::BOSSCORE, x - 2, y + 7, 500, coreSprite, 0);
        enemies[1].spawn(EnemyType::BOSS_CORE, x, y, 200, bodySheet, 1);
        enemies[2].spawn(EnemyType::BOSS_BOTTOM_WING, x, y + 22, 200, bodySheet, 2);
        enemies[3].spawn(EnemyType::BOSS_TOP_WING, x, y - 21, 200, bodySheet, 0);
        break;
    }
    hp = 100;
}

int8_t dbf BossEnemy::hit(BoundBox bounds) {
    for (uint8_t i = 0; i < 6; i++) {
        if (enemies[i].active) {
            if (enemies[i].hit(bounds)) {
                return i;
            }
        }
    }
    return -1;
}

void BossEnemy::blink() {
    switch (type) {
    case BossType::L1:
        Sprites::drawErase(x - (frame % 2) - 1, y + 7, coreSprite, 0);
        break;
    }
}

void BossEnemy::tick(Bullet *enemyBullets) {
    ticker++;
    if (x > 80) {
        x--;
    }
    if (ticker % 15 == 0) {
        frame++;
        if (frame > 3) {
            frame = 0;
        }
    }
    if (ticker == 61) {
        ticker = 0;
    }
    for (uint8_t i = 0; i < 6; i++) {
        enemies[i].tick(enemyBullets);
    }
}