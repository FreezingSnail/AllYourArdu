#pragma once
#include "lib/boundBox.hpp"
#include <Arduboy2.h>
#include <stdint.h>

enum class BulletType {
  DOT,
  LINE,
  CIRCLE,
  TRIANGLE,
};

class Bullet {
public:
  uint8_t x, y;
  bool active;
  BulletType type;

  void draw();
  void tick();
  void start(uint8_t x, uint8_t y, uint8_t type);
  BoundBox getBounding();
};