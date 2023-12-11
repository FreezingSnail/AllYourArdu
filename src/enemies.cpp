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

  for (uint8_t i = 0; i < ENEMIES; i++) {
    enemies[i].tick();
    for (uint8_t j = 0; j < BULLETCOUNT; j++) {
      if (playerBullets[j].active) {
        BoundBox bulBox = playerBullets[j].getBounding();
        BoundBox eBox = enemies[i].getBounding();
        if (enemies[i].hit(bulBox)) {
          enemies[i].active = false;
          playerBullets[j].active = false;
          score++;
          break;
        }
      }
    }
  }
  if (ticker == 40) {
    ticker = 0;
    for (uint8_t i = 0; i < ENEMIES; i++) {
      if (!enemies[i].active) {
        enemies[i].spawn((rand() % 50 + 10));
        break;
      }
    }
  }
}