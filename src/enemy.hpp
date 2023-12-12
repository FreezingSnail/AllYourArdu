#pragma once
#include "lib/boundBox.hpp"
#include "lib/paths.hpp"
#include "lib/types.hpp"
#include <Arduboy2.h>
#include <stdint.h>

class Enemy {
  public:
    int16_t x, y;
    Pattern pattern;
    bool active;
    EnemyType type;
    uint8_t ticker;
    uint8_t frame;
    uint8_t stepCount;
    uint8_t stepPointer;

    void tick();
    void draw();
    void spawn(EnemyType type, uint8_t x, uint8_t y);
    void despawn();
    BoundBox getBounding();
    bool hit(BoundBox bulletBox);
    void reset();
    void applyPath(Path p);
};