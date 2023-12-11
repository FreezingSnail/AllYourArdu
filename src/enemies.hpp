#pragma once
#include "bullet.hpp"
#include "enemy.hpp"
#include "globals.hpp"

class Enemies {
public:
  Enemy enemies[ENEMIES];
  uint8_t ticker;
  Bullet *playerBullets;
  uint16_t score;

  Enemies();
  void tick();
};