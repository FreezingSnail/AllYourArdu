#pragma once
constexpr uint8_t explosionWidth = 8;
constexpr uint8_t explosionHeight = 8;

const uint8_t PROGMEM explosion[] =
{
  explosionWidth, explosionHeight,
  //Frame 0
  0x3C, 0x7E, 0xBF, 0x87, 0xE7, 0x97, 0x12, 0x3C, 

  //Frame 1
  0x3C, 0x7E, 0x87, 0xF3, 0x8B, 0x0B, 0x0A, 0x1C, 

  //Frame 2
  0x3C, 0x7E, 0xF7, 0x8B, 0x07, 0x07, 0x06, 0x0C, 

  //Frame 3
  0x3C, 0x7E, 0xBF, 0x07, 0x07, 0x07, 0x02, 0x04, 

  //Frame 4
  0x3C, 0x7E, 0x07, 0x03, 0x03, 0x03, 0x02, 0x00, 

  //Frame 5
  0x3C, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00
};
