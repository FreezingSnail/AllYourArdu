#include "lilship.hpp"
#include "../globals.hpp"
#include "../sprites/miniShips.h"
#include <Arduboy2.h>

#define x *rootX + xMod
#define y *rootY + yMod

static int8_t XSPIN[] = {-15, -5, 5, 15, 25, 15, 5, -5};
static int8_t YSPIN[] = {5, -5, -15, -5, 5, 15, 25, 15};

void LilShip::tick(Enemy *enemies) {
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
    if (changingPattern) {
        changePattern();
    }
}

void LilShip::draw() {
    // getBound().draw();
    Sprites::drawOverwrite(x, y, miniShips, (4 * (frame)) + uint8_t(type));
}

void LilShip::spawn(uint8_t *xRoot, uint8_t *yRoot, int8_t xMod, int8_t yMod) {
    this->rootX = xRoot;
    this->rootY = yRoot;
    this->xMod = xMod;
    this->yMod = yMod;
}

void dbf LilShip::despawn() {
    this->active = false;
}

BoundBox LilShip::getBound() {
    return BoundBox(x + 1, y + 1, 5, 3);
}

void LilShip::setChange(int8_t xMod, int8_t yMod, Formation formation) {
    xchange = xMod;
    ychange = yMod;
    changingPattern = true;
    this->formation = formation;
}

void LilShip::changePattern() {
    if (yMod > ychange) {
        yMod--;
    } else if (yMod < ychange) {
        yMod++;
    }

    if (xMod > xchange) {
        xMod--;
    } else if (xMod < xchange) {
        xMod++;
    }

    if (xMod == xchange && yMod == ychange) {
        if (formation != Formation::SPIN) {
            changingPattern = false;
            return;
        }
        movePointer++;
        if (movePointer > 7)
            movePointer = 0;
        ychange = YSPIN[movePointer];
        xchange = XSPIN[movePointer];
    }
}

void LilShip::setSpin(uint8_t p) {
    movePointer = p;
    formation = Formation::SPIN;
    changingPattern = true;
}

uint8_t LilShip::getX() {
    return x;
}

uint8_t LilShip::getY() {
    return y;
}