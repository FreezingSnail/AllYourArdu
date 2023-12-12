#include "lilship.hpp"
#include "../globals.hpp"
#include "../sprites/miniShips.h"
#include <Arduboy2.h>

void LilShip::tick() {
    if (!active) {
        return;
    }
    ticker++;
    if (ticker % 5 == 0) {
        frame++;
        if (frame > 3) {
            frame = 0;
        }
    }
    draw();
}

void LilShip::draw() {
    if (top) {
        Sprites::drawSelfMasked(*x, *y - 10, miniShips, (4 * (frame)) + uint8_t(type));
    } else {
        Sprites::drawSelfMasked(*x, *y + 18, miniShips, (4 * (frame)) + uint8_t(type));
    }
}

void LilShip::spawn(uint8_t *x, uint8_t *y) {
    this->x = x;
    this->y = y;
}

void LilShip::despawn() {
    this->active = false;
}