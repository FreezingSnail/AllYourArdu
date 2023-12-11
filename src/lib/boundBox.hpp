#pragma once
#include <Arduboy2.h>
#include <stdint.h>

class BoundBox {
private:
  uint8_t x, y, width, height;

public:
  BoundBox(int x, int y, int width, int height)
      : x(x), y(y), width(width), height(height) {}
  bool BoundBox::overlap(BoundBox box) {
    if (x + width <= box.x || box.x + box.width <= x) {
      return false;
    }

    if (y + height <= box.y || box.y + box.height <= y) {
      return false;
    }

    return true;
  };
  void BoundBox::draw() { Arduboy2::drawRect(x, y, width, height); };
};
