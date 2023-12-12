#pragma once
#include "bullet.hpp"
#include "enemy.hpp"
#include "globals.hpp"
#include "powerup.hpp"

class Enemies {
  public:
    Enemy enemies[ENEMIES];
    uint16_t ticker;
    Bullet *playerBullets;
    uint16_t score;
    uint8_t powerupTimer;
    PowerUp powerups;
    bool activePowerUp;

    Enemies();
    void tick();
    void spawn(EnemyType type, uint8_t x, uint8_t y);
};