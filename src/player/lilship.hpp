#pragma once
#include "../globals.hpp"
#include <stdint.h>

class LilShip {
  public:
    uint8_t *x, *y;
    bool active;
    ShipType type;
    uint8_t ticker, frame;
    bool top;

    void draw();
    void spawn(uint8_t *x, uint8_t *y);
    void despawn();
    void tick();
};