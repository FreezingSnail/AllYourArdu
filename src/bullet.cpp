#include "bullet.hpp"
#include "globals.hpp"

void Bullet::draw() {
    getBounding().draw();
    switch (type) {
    case BulletType::DOT:
        Arduboy2::drawPixel(x, y);
        break;
    case BulletType::LINE:
        Arduboy2::drawLine(x - 5, y, x, y, WHITE);
        break;
    case BulletType::CIRCLE:
        Arduboy2::drawCircle(x, y, 3, WHITE);
        break;
    case BulletType::TRIANGLE:
        Arduboy2::drawTriangle(x + 5, y, x, y - 2, x, y + 2, WHITE);
        break;
    }
}

void Bullet::tick() {
    if (!active) {
        return;
    }
    move();
    this->draw();
    if (x > 127 || y < -5 || y > 132) {
        reset();
    }
}

void Bullet::move() {
    stepCount++;
    switch (type) {
    case BulletType::DOT:
        applyPath(STRAIGHT_PATH[0]);
        applyPath(STRAIGHT_PATH[0]);
        applyPath(STRAIGHT_PATH[0]);
        break;
    case BulletType::LINE:
        applyPath(STRAIGHT_PATH[0]);
        applyPath(STRAIGHT_PATH[0]);
        break;
    case BulletType::CIRCLE:
        if (stepCount > BALL_PATH[stepPointer].stepCount) {
            stepCount = 0;
            stepPointer++;
            if (stepPointer == BALL_STEPS) {
                stepPointer = 1;
            }
        }
        applyPath(BALL_PATH[stepPointer]);
        break;
    case BulletType::TRIANGLE:
        if (stepCount > TRI_PATH[stepPointer].stepCount) {
            stepCount = 0;
            stepPointer++;
            if (stepPointer == TRI_STEPS) {
                stepPointer = 0;
            }
        }
        applyPath(TRI_PATH[stepPointer]);
        break;
    }
}

void Bullet::applyPath(Path p) {
    int8_t xDiff = (xMod * p.xMod);
    if (enemy)
        xDiff *= -1;
    x += xDiff;
    y += (yMod * p.yMod);
}

void dbf Bullet::start(uint8_t x, uint8_t y, uint8_t type, int8_t xMod, int8_t yMod) {
    active = true;
    this->x = x;
    this->y = y;
    this->enemy = false;
    this->type = BulletType(type);
    if (this->type == BulletType::TRIANGLE || this->type == BulletType::CIRCLE) {
        this->xMod = xMod;
        this->yMod = yMod;
    } else {
        this->xMod = 1;
        this->yMod = 1;
    }
}

void Bullet::start(uint8_t x, uint8_t y, uint8_t type, int8_t xMod, int8_t yMod, bool enemy) {
    start(x, y, type, xMod, yMod);
    this->enemy = enemy;
}

BoundBox Bullet::getBounding() {
    switch (type) {
    case BulletType::DOT:
        return BoundBox(x, y, 0, 0);
    case BulletType::LINE:
        return BoundBox(x - 5, y, 5, 0);
    case BulletType::CIRCLE:
        return BoundBox(x - 2, y - 2, 5, 5);
    case BulletType::TRIANGLE:
        return BoundBox(x - 1, y - 2, 2, 2);
    }
}

void Bullet::reset() {
    active = false;
    x = 255;
    y = 255;
    stepCount = 0;
    stepPointer = 0;
    this->xMod = 1;
    this->yMod = 1;
}

uint8_t Bullet::getDamage() {
    switch (type) {
    case BulletType::DOT:
        return 1;
    case BulletType::LINE:
        return 2;
    case BulletType::CIRCLE:
        return 3;
    case BulletType::TRIANGLE:
        return 4;
    }
}