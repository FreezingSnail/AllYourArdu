#include "enemies.hpp"
#include "globals.hpp"

Enemies::Enemies() {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies[i].type = EnemyType::HEAD;
        enemies[i].active = false;
    }
    score = 0;
}

void Enemies::tick() {
    ticker++;
    if (ticker % 60 == 0) {
        powerupTimer++;
    }

    if (powerupTimer % 30 == 0 && !powerups.active) {
        uint8_t index = rand() % 4;
        powerups.spawn(rand() % 40 + 60, rand() % 20 + 20, index);
    }

    powerups.draw();
}

void Enemies::spawn(EnemyType type, uint8_t x, uint8_t y) {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].spawn(type, x, y);
            return;
        }
    }
}

void dbf Enemies::spawnBrokenWall(EnemyType type, int16_t x, int16_t y, uint16_t stepCounter, uint8_t stepPointer) {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].spawnBrokenWall(type, x, y, stepCounter, stepPointer);
            return;
        }
    }
}