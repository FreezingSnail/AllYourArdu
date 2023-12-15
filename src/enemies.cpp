#include "enemies.hpp"
#include "globals.hpp"

Enemies::Enemies() {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies[i].type = EnemyType::HEAD;
        enemies[i].active = false;
        enemies[i].x = 254;
        enemies[i].y = 254;
    }
    score = 0;
    powerups.x = 255;
    powerups.y = 255;
}

void Enemies::tick() {
    ticker++;
    if (ticker % 60 == 0) {
        powerupTimer++;
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

void Enemies::spawnBrokenWall(EnemyType type, int16_t x, int16_t y, uint16_t stepCounter, uint8_t stepPointer) {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].spawnBrokenWall(type, x, y, stepCounter, stepPointer);
            return;
        }
    }
}

void Enemies::powerUpSpawn(uint8_t x, uint8_t y) {
    uint8_t rate = rand() % 100;
    if (rate < 60) {
        return;
    }
    if (!powerups.active) {
        uint8_t index = rand() % 4;
        powerups.spawn(x, y, index);
    }
}