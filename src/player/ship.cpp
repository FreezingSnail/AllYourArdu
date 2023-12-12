#include "ship.hpp"
#include "../globals.hpp"
#include "../sprites/mainship.h"
#define SUBPIXELMOD 1

static void printPowerUp(Arduboy2 &arduboy, ShipType type) {
    switch (type) {
    case ShipType::MINI:
        arduboy.print(F("\x07"));
        break;
    case ShipType::ROD:
        arduboy.print(F("-"));
        break;
    case ShipType::EYE:
        arduboy.print(F("\x09"));
        break;
    case ShipType::BOMB:
        arduboy.print(F("\x10"));
        break;
    }
}

void Ship::init() {
    this->powerupPointer--;
    this->x = 10;
    this->y = 10;
    this->suby = 10 * SUBPIXELMOD;
    this->subx = 10 * SUBPIXELMOD;
    this->pushPower(ShipType::MINI);
    this->pushPower(ShipType::ROD);
    this->pushPower(ShipType::EYE);
    this->pushPower(ShipType::BOMB);

    lilShips[0].spawn(&x, &y);
    lilShips[0].top = true;
    lilShips[1].spawn(&x, &y);
}

void Ship::run() {
    ticker++;
    if (ticker % 5 == 0) {
        lilframe++;
        if (lilframe > 3) {
            lilframe = 0;
        }
        if (frame == 0) {
            frame = 1;
        } else {
            frame = 0;
        }
    }

    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (enemies[i].active) {
            if (getBound().overlap(enemies[i].getBounding())) {
                //*state = GameState::LOSE;
                break;
            }
        }
    }

    if (getBound().overlap(powerup->getBound())) {
        powerup->despawn();
        pushPower(powerup->type);
    }

    draw();
    move();
    littleShip();
    bulletTick();
}
void Ship::draw() {
    Sprites::drawSelfMasked(x, y, mainship, frame);
    arduboy->setCursor(20, 0);
    arduboy->print(F("P:"));
    for (uint8_t i = 0; i <= powerupPointer; i++) {
        printPowerUp(*arduboy, powerups[i]);
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
    lilShips[0].tick();
    lilShips[1].tick();

    if (Arduboy2::justPressed(B_BUTTON)) {
        if (powerupPointer >= 0) {
            spawnBulletShip(powerups[0]);
            popPower();
        }
    }
}

void Ship::bulletTick() {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        playerBullets[i].tick();
    }

    if (Arduboy2::justPressed(A_BUTTON) || (Arduboy2::pressed(A_BUTTON) && (ticker % 10 == 0))) {
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

BoundBox Ship::getBound() {
    return BoundBox(x, y, 16, 16);
}

void Ship::spawnBulletShip(ShipType type) {
    lilShips[0].active = true;
    lilShips[0].type = type;
    lilShips[1].active = true;
    lilShips[1].type = type;
    littleShipIndex = uint8_t(type);
    littleShips = true;
}

void Ship::pushPower(ShipType type) {
    if (powerupPointer == 7) {
        return;
    }
    powerupPointer++;
    powerups[powerupPointer] = type;
}
void Ship::popPower() {
    for (int8_t i = 0; i < powerupPointer; i++) {
        powerups[i] = powerups[i + 1];
    }
    powerupPointer--;
}