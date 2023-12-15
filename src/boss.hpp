#pragma once
#include "enemy.hpp"
#include "lib/bossdata.hpp"
#include "lib/boundBox.hpp"
#include "bullet.hpp"

class BossEnemy {
  public:
    const uint8_t *coreSprite;
    const uint8_t *bodySheet;
    BossType type;
    uint16_t x, y;
    bool vertical;
    bool active;
    uint8_t ticker;
    uint8_t frame;
    uint8_t hp;
    Enemy enemies[6];

    void load(BossData *const data);
    int8_t hit(BoundBox bounds);
    void tick(Bullet *enemyBullets);
    bool bossActive();
};