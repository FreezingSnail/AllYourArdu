#pragma once
#include "../bullet.hpp"
#include "../enemy.hpp"
#include "../gamestate.hpp"
#include "../lib/boundBox.hpp"
#include "../powerup.hpp"
#include "lilship.hpp"
#include <Arduboy2.h>
#include <stdint.h>

class Ship {
  public:
    uint8_t x, y;
    int16_t subx, suby;
    uint8_t frame, ticker, lilframe;
    bool littleShipsActive;
    uint8_t littleShipIndex;
    Bullet *playerBullets;
    Enemy *enemies;
    PowerUp *powerup;
    GameState *state;
    LilShip lilShips[2];
    uint8_t lilshipBollArray;
    ShipType powerups[8];
    int8_t powerupPointer;
    Arduboy2 *arduboy;
    Formation formation;

    void init();
    void run();
    void draw();
    void move();
    void littleShip();
    void bulletTick();
    void spawnBulletShip(ShipType type);
    BoundBox getBound();
    void pushPower(ShipType type);
    void popPower();
    void formChange();
};