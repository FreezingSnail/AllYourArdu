#include "bullet.hpp"

void Bullet::draw() {
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
    x += 2;
    this->draw();
    if (x > 127) {
        active = false;
        x = 0;
        y = 0;
    }
}

void Bullet::start(uint8_t x, uint8_t y, uint8_t type) {
    active = true;
    this->x = x;
    this->y = y;
    this->type = BulletType(type);
}

BoundBox Bullet::getBounding() {
    switch (type) {
    case BulletType::DOT:
        return BoundBox(x, y, 0, 0);
    case BulletType::LINE:
        return BoundBox(x - 5, y, 5, 0);
    case BulletType::CIRCLE:
        return BoundBox(x + 1, y + 1, 2, 2);
    case BulletType::TRIANGLE:
        return BoundBox(x - 1, y - 2, 2, 2);
    }
}

void Bullet::reset() {
    active = false;
    x = 255;
    y = 255;
}