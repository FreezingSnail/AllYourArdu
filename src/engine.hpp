#pragma once
#include "enemies.hpp"
#include "globals.hpp"
#include "lib/levels.hpp"
#include "player/ship.hpp"

class Engine {
  public:
    Bullet playerBullets[BULLETCOUNT];
    Bullet enemyBullets[BULLETCOUNT];
    Ship ship;
    Enemies enemies;
    GameState state;
    uint16_t ticker;
    Level const *currentLevel;
    uint8_t currentLevelIndex;
    uint8_t currentSpawnIndex;
    uint8_t spawnCounter;
    EnemyType debug;

    Engine();
    void run();
    void restart();
    void loadLevel(uint8_t level);
    void spawn();
};