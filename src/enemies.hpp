#pragma once
#include "bullet.hpp"
#include "enemy.hpp"
#define ENEMIES 30

class Enemies {
public:
  Enemy enemies[ENEMIES];
  uint8_t ticker;
  uint8_t debug;
  Bullet *playerBullets;
  uint16_t score;

  Enemies();
  void tick();
};