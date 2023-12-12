#include "enemies.hpp"
#include "globals.hpp"

Enemies::Enemies() {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies[i].type = EnemyType::HEAD;
        enemies[i].active = false;
    }
    score = 0;
}

void dbf Enemies::tick() {
    ticker++;
    if (ticker % 60 == 0) {
        powerupTimer++;
    }

    if (powerupTimer % 30 == 0 && !powerups.active) {
        uint8_t index = rand() % 4;
        powerups.spawn(rand() % 40 + 60, rand() % 20 + 20, index);
    }

    powerups.draw();

    for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies[i].tick();
        for (uint8_t j = 0; j < BULLETCOUNT; j++) {
            bool hit = false;
            if (playerBullets[j].active) {
                if (enemies[i].hit(playerBullets[j].getBounding())) {
                    enemies[i].reset();
                    playerBullets[j].reset();
                    score++;
                    hit = true;
                    continue;
                }
            }
            if (hit) {
                break;
            }
        }
    }
    if (ticker % 40 == 0) {
        for (uint8_t i = 0; i < ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].spawn((rand() % 50 + 10));
                break;
            }
        }
    }
}