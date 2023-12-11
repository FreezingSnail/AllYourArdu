#pragma once
#include <Arduboy2.h>
#include <stdint.h>

#include "bullet.hpp"

class Ship {
public:
  uint8_t x, y;
  int16_t subx, suby;
  uint8_t frame, ticker;
  bool littleShips;
  uint8_t littleShipIndex;
  Bullet *playerBullets;

  Ship();
  void run();
  void draw();
  void move();
  void littleShip();
  void bulletTick();
};