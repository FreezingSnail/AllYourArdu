#pragma once
#include "globals.hpp"
#include "lib/boundBox.hpp"
#include "sprites/powerups.h"
#include <stdint.h>

class PowerUp {
  public:
    uint8_t x, y;
    bool active;
    ShipType type;

    void spawn(uint8_t x, uint8_t y, uint8_t type) {
        this->x = x;
        this->y = y;
        active = true;
        this->type = ShipType(type);
    };

    void despawn() {
        x = 0;
        y = 240;
        active = false;
    };

    void draw() {
        if (!active) {
            return;
        }
        Sprites::drawSelfMasked(x, y, powerups, uint8_t(type));
    };

    BoundBox getBound() {
        return BoundBox(x + 1, y + 1, 6, 6);
    };
};