#pragma once
#include "lib/boundBox.hpp"
#include <Arduboy2.h>
#include <stdint.h>

enum class Pattern {
    STRAIGHT,
    ZIGZAG,
};

enum class EnemyType {
    HEAD,
};

class Enemy {
  public:
    int16_t x, y;
    Pattern pattern;
    bool active;
    EnemyType type;
    uint8_t ticker;

    void tick();
    void draw();
    void spawn(uint8_t y);
    void despawn();
    BoundBox getBounding();
    bool hit(BoundBox bulletBox);
    void reset();
};