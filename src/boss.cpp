#include "boss.hpp"
#include "globals.hpp"
#include "lib/bossdata.hpp"
#include <Arduboy2.h>

void BossEnemy::load(BossData *const data) {
    x = 128;
    y = 24;
    coreSprite = pgm_read_ptr(&data->core);
    bodySheet = pgm_read_ptr(&data->sheet);
    type = static_cast<BossType>(pgm_read_byte(&data->type));
    vertical = pgm_read_byte(&data->vertical);
    active = true;
    switch (type) {
    case BossType::L5:
        enemies[0].spawn(EnemyType::BOSSCORE, x - 2, y + 7, 500, coreSprite, 0);
        enemies[1].spawn(EnemyType::BOSS_CORE, x, y, 200, bodySheet, 1);
        enemies[2].spawn(EnemyType::BOSS_BOTTOM_WING, x, y + 22, 200, bodySheet, 2);
        enemies[3].spawn(EnemyType::BOSS_TOP_WING, x, y - 21, 200, bodySheet, 0);
        break;

    case BossType::L1:
        enemies[0].spawn(EnemyType::BOSS_FRONT, x, y, 200, bodySheet, 0);
        enemies[1].spawn(EnemyType::BOSS_MIDDLE, x + 24, y, 200, bodySheet, 1);
        enemies[2].spawn(EnemyType::BOSS_BACK, x + 48, y, 200, bodySheet, 2);
        enemies[3].spawn(EnemyType::BOSSCORELONG, x - 2, y + 8, 500, coreSprite, 0);
        enemies[4].spawn(EnemyType::BOSSCORELONG, x + 22, y + 8, 500, coreSprite, 0);
        enemies[5].spawn(EnemyType::BOSSCORELONG, x + 46, y + 5, 500, coreSprite, 0);
        break;
    }
}

int8_t BossEnemy::hit(BoundBox bounds) {
    for (uint8_t i = 0; i < 6; i++) {
        if (enemies[i].active) {
            if (enemies[i].hit(bounds)) {
                return i;
            }
        }
    }
    return -1;
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

bool BossEnemy::bossActive() {
    for (uint8_t i = 0; i < 6; i++) {
        if (enemies[i].active && (enemies[i].type == EnemyType::BOSSCORE || enemies[i].type == EnemyType::BOSSCORELONG)) {
            return true;
        }
    }
    return false;
}
