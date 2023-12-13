#pragma once
#include "../enemy.hpp"
#include "../globals.hpp"
#include "../lib/boundBox.hpp"
#include <stdint.h>

class LilShip {
  public:
    uint8_t *rootX, *rootY;
    int8_t xMod, yMod;
    bool active;
    ShipType type;
    uint8_t ticker, frame;
    int8_t xchange, ychange;
    bool changingPattern;
    Formation formation;
    uint8_t movePointer;

    void draw();
    void spawn(uint8_t *x, uint8_t *y, int8_t xMod, int8_t yMod);
    void despawn();
    void tick(Enemy *enemies);
    BoundBox getBound();
    void setChange(int8_t xMod, int8_t yMod, Formation formation);
    uint8_t getX();
    uint8_t getY();
    void changePattern();
    void setSpin(uint8_t movePointer);
};