#pragma once
#include "bullet.hpp"
#include "lib/boundBox.hpp"
#include "lib/paths.hpp"
#include "lib/types.hpp"
#include <Arduboy2.h>
#include <stdint.h>

class Enemy {
  public:
    int16_t x, y;
    int16_t subx, suby;
    uint8_t SUBPIXELMOD;

    Pattern pattern;
    bool active;
    EnemyType type;
    uint8_t ticker;
    uint8_t frame;
    uint16_t stepCount;
    uint8_t stepPointer;
    int16_t hitCounter;

    void tick(Bullet *enemyBullets);
    void draw();
    void blink();
    void spawn(EnemyType type, int16_t x, int16_t y);
    void spawnBrokenWall(EnemyType type, int16_t x, int16_t y, uint8_t stepCounter, uint8_t stepPointer);
    void despawn();
    BoundBox getBounding();
    BoundBox getCollision();
    bool hit(BoundBox bulletBox);
    void reset();
    void applyPath(Path p);
    bool takeDamage(uint8_t damage);
    bool shoot();
    void bullet(Bullet *enemyBullets);
};