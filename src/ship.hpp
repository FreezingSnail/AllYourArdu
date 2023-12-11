#pragma once
#include "bullet.hpp"
#include "enemy.hpp"
#include "gamestate.hpp"
#include "lib/boundBox.hpp"
#include <Arduboy2.h>
#include <stdint.h>

class Ship {
public:
  uint8_t x, y;
  int16_t subx, suby;
  uint8_t frame, ticker;
  bool littleShips;
  uint8_t littleShipIndex;
  Bullet *playerBullets;
  Enemy *enemies;
  GameState *state;

  Ship();
  void run();
  void draw();
  void move();
  void littleShip();
  void bulletTick();
  BoundBox getBound();
  bool hit(BoundBox enemy);
};