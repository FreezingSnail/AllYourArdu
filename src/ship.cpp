#include "ship.hpp"
#include "globals.hpp"
#include "sprites/mainship.h"
#include "sprites/miniShips.h"
#define SUBPIXELMOD 2

Ship::Ship() {
  x = 10;
  y = 10;
  littleShips = false;
}

void Ship::run() {
  ticker++;
  if (ticker == 10) {
    if (frame == 0) {
      frame = 1;
    } else {
      frame = 0;
    }
    ticker = 0;
  }

  for (uint8_t i = 0; i < ENEMIES; i++) {
    if (enemies[i].active) {
      if (getBound().overlap(enemies[i].getBounding())) {
        *state = GameState::LOSE;
        break;
      }
    }
  }

  draw();
  move();
  littleShip();
  bulletTick();
}
void Ship::draw() {
  Sprites::drawOverwrite(x, y, mainship, frame);
  if (littleShips) {
    Sprites::drawOverwrite(x, y - 10, miniShips, littleShipIndex);
    Sprites::drawOverwrite(x, y + 18, miniShips, littleShipIndex);
  }
}

void dbf Ship::move() {
  if (Arduboy2::pressed(LEFT_BUTTON)) {
    subx--;
  }
  if (Arduboy2::pressed(RIGHT_BUTTON)) {
    subx++;
  }
  if (Arduboy2::pressed(UP_BUTTON)) {
    suby--;
  }
  if (Arduboy2::pressed(DOWN_BUTTON)) {
    suby++;
  }

  if (suby < 0) {
    suby = 0;
  }
  if (subx < 0) {
    subx = 0;
  }
  if (subx >= ((128 * SUBPIXELMOD) - (16 * SUBPIXELMOD))) {
    subx = ((128 * SUBPIXELMOD) - (16 * SUBPIXELMOD));
  }
  if (suby >= ((64 * SUBPIXELMOD) - (16 * SUBPIXELMOD))) {
    suby = ((64 * SUBPIXELMOD) - (16 * SUBPIXELMOD));
  }

  x = subx / SUBPIXELMOD;
  y = suby / SUBPIXELMOD;
}

void Ship::littleShip() {
  if (Arduboy2::justPressed(B_BUTTON)) {
    if (littleShips) {
      littleShipIndex++;
    } else {
      littleShips = true;
    }
    if (littleShipIndex > 3) {
      littleShipIndex = 0;
      littleShips = false;
    }
  }
}

void Ship::bulletTick() {
  for (uint8_t i = 0; i < BULLETCOUNT; i++) {
    playerBullets[i].tick();
  }

  if (Arduboy2::justPressed(A_BUTTON)) {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
      if (!playerBullets[i].active) {
        playerBullets[i].start(x + 16, y + 8, littleShipIndex);
        break;
      }
    }
    if (littleShips) {
      for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        if (!playerBullets[i].active) {
          playerBullets[i].start(x + 2, y - 6, littleShipIndex);
          break;
        }
      }
      for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        if (!playerBullets[i].active) {
          playerBullets[i].start(x + 2, y + 22, littleShipIndex);
          break;
        }
      }
    }
  }
}

BoundBox Ship::getBound() { return BoundBox(x, y, 16, 16); }