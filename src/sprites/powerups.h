#pragma once
constexpr uint8_t powerupsWidth = 8;
constexpr uint8_t powerupsHeight = 8;

const uint8_t PROGMEM powerups[] =
{
  powerupsWidth, powerupsHeight,
  //Frame 0
  0xBD, 0x42, 0x81, 0x99, 0x99, 0x81, 0x42, 0xBD, 

  //Frame 1
  0xBD, 0x42, 0x99, 0x99, 0x99, 0x99, 0x42, 0xBD, 

  //Frame 2
  0xBD, 0x42, 0x99, 0xA5, 0xA5, 0x99, 0x42, 0xBD, 

  //Frame 3
  0xBD, 0x42, 0x81, 0xBD, 0x99, 0x81, 0x42, 0xBD
};
