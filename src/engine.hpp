#pragma once
#include "boss.hpp"
#include "enemies.hpp"
#include "explosion.hpp"
#include "globals.hpp"
#include "lib/levels.hpp"
#include "player/ship.hpp"

class Engine {
  public:
    Bullet playerBullets[BULLETCOUNT];
    Bullet enemyBullets[BULLETCOUNT];
    Explosion explosions[8];
    Ship ship;
    Enemies enemies;
    GameState state;
    uint16_t ticker;
    Level const *currentLevel;
    uint8_t currentLevelIndex;
    uint8_t currentSpawnIndex;
    uint8_t spawnCounter;

    BossEnemy boss;

    Engine();
    void run();
    void restart();
    void loadLevel(uint8_t level);
    void spawn();
    void bulletTick();
    bool clearedEnemies();

    void spawnExplode(uint8_t x, uint8_t y, uint8_t size);
};