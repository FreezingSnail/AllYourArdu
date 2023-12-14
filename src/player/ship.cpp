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

    lilShips[0].spawn(&x, &y, 0, -10);
    lilShips[1].spawn(&x, &y, 0, 18);
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

    if (getBound().overlap(powerup->getBound())) {
        powerup->despawn();
        spawnBulletShip(powerup->type);
        pushPower(powerup->type);
    }

    draw();
    move();
    littleShip();

    if (Arduboy2::justPressed(LEFT_BUTTON) && Arduboy2::justPressed(RIGHT_BUTTON)) {
        popPower();
        return;
    }
    bulletTick();
}
void Ship::draw() {
    Sprites::drawOverwrite(x, y, mainship, frame);
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
    lilShips[0].tick(enemies);
    lilShips[1].tick(enemies);

    if (Arduboy2::justPressed(B_BUTTON)) {
        formChange();
        // if (powerupPointer >= 0) {
        //     spawnBulletShip(powerups[0]);
        //     popPower();
        // }
    }
}

void Ship::bulletTick() {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        playerBullets[i].tick();
    }

    if (Arduboy2::justPressed(A_BUTTON) || (Arduboy2::pressed(A_BUTTON) && (ticker % 15 == 0))) {
        for (uint8_t i = 0; i < BULLETCOUNT; i++) {
            if (!playerBullets[i].active) {
                playerBullets[i].start(x + 16, y + 8, littleShipIndex, 1, 0);
                break;
            }
        }
        if (lilShips[0].active) {
            for (uint8_t i = 0; i < BULLETCOUNT; i++) {
                if (!playerBullets[i].active) {
                    playerBullets[i].start(lilShips[0].getX() + 4, lilShips[0].getY() + 4, littleShipIndex, 1, -1);
                    break;
                }
            }
        }
        if (lilShips[1].active) {
            for (uint8_t i = 0; i < BULLETCOUNT; i++) {
                if (!playerBullets[i].active) {
                    playerBullets[i].start(lilShips[1].getX() + 4, lilShips[1].getY() + 4, littleShipIndex, 1, 1);
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
    littleShipsActive = true;
}

void Ship::pushPower(ShipType type) {
    if (powerupPointer == 7) {
        return;
    }
    powerupPointer++;
    powerups[powerupPointer] = type;
}
void Ship::popPower() {
    ShipType type = powerups[0];
    for (int8_t i = 0; i < powerupPointer; i++) {
        powerups[i] = powerups[i + 1];
    }
    powerupPointer--;
    lilShips[0].despawn();
    lilShips[1].despawn();
    if (powerupPointer >= 0) {
        spawnBulletShip(type);
    } else {
        littleShipsActive = false;
        littleShipIndex = 0;
    }
}

void Ship::formChange() {
    formation = Formation(uint8_t(formation) + 1);
    if (formation == Formation::NONE)
        formation = Formation(0);

    switch (formation) {
    // case Formation::TIGHT:
    //     lilShips[0].setChange(-8, -2);
    //     lilShips[1].setChange(-8, 10);
    //     break;
    case Formation::WIDE:
        lilShips[0].setChange(0, -10, Formation::TOP);
        lilShips[1].setChange(0, 18, Formation::TOP);
        break;
    case Formation::FRONT:
        lilShips[0].setChange(18, -2, Formation::TOP);
        lilShips[1].setChange(18, 10, Formation::TOP);
        break;
    case Formation::BOTTOM:
        lilShips[1].setChange(-7, 30, Formation::TOP);
        lilShips[0].setChange(-7, 18, Formation::TOP);
        break;
    case Formation::TOP:
        lilShips[1].setChange(-7, -8, Formation::TOP);
        lilShips[0].setChange(-7, -20, Formation::TOP);
        break;
    case Formation::SPIN:
        lilShips[1].setSpin(0);
        lilShips[0].setSpin(2);
    }
}