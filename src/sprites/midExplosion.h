#pragma once
constexpr uint8_t midExplosionWidth = 16;
constexpr uint8_t midExplosionHeight = 16;

const uint8_t PROGMEM midExplosion[] =
{
  midExplosionWidth, midExplosionHeight,
  //Frame 0
  0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C, 0xF8, 0x04, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 
  0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C, 0x04, 0x04, 0x02, 0x01, 

  //Frame 1
  0xF8, 0x04, 0x02, 0x01, 0x81, 0x81, 0x41, 0xF1, 0x4D, 0x82, 0x85, 0xF9, 0x01, 0x01, 0x02, 0x0C, 
  0x00, 0x01, 0x02, 0x1E, 0x65, 0x44, 0x84, 0x85, 0x86, 0x4A, 0x71, 0x1E, 0x10, 0x10, 0x08, 0x06, 

  //Frame 2
  0xF0, 0x48, 0x24, 0x12, 0x12, 0xF1, 0x19, 0x17, 0x23, 0x41, 0x83, 0x03, 0x06, 0x0E, 0xF8, 0xF0, 
  0x1F, 0x24, 0x48, 0x90, 0x90, 0xA7, 0xA8, 0xB0, 0x60, 0x60, 0x5F, 0x50, 0x28, 0x34, 0x0B, 0x07, 

  //Frame 3
  0xC0, 0x30, 0x08, 0xE4, 0x9A, 0x46, 0x43, 0x41, 0x41, 0x41, 0x41, 0x41, 0x82, 0x06, 0x1C, 0xE8, 
  0x07, 0x1C, 0x63, 0x43, 0x8C, 0x90, 0x20, 0x40, 0x40, 0x40, 0x40, 0x40, 0xA0, 0xD1, 0x6F, 0x3F, 

  //Frame 4
  0x02, 0xE5, 0x52, 0x48, 0xF4, 0x2A, 0x26, 0x22, 0x22, 0x42, 0x42, 0x86, 0x0C, 0x18, 0xF0, 0x00, 
  0x0E, 0x33, 0x44, 0x48, 0x91, 0xA2, 0xA4, 0xA8, 0xA8, 0x68, 0x68, 0x39, 0x0E, 0x66, 0x63, 0x00, 

  //Frame 5
  0x06, 0x09, 0xE9, 0xD6, 0x48, 0x24, 0xF2, 0x2A, 0x46, 0xC2, 0x02, 0x06, 0x0C, 0x18, 0xF0, 0x00, 
  0x00, 0x00, 0x0F, 0x38, 0x30, 0x60, 0x41, 0x42, 0x64, 0x78, 0x4F, 0x28, 0x14, 0x4A, 0xA7, 0x40, 

  //Frame 6
  0x0C, 0x12, 0x12, 0x12, 0xCC, 0xB0, 0x90, 0x88, 0x78, 0x8C, 0x0C, 0x14, 0xBC, 0xF0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0E, 0x13, 0x2C, 0x28, 0x30, 0x11, 0x1F, 0x11, 0x09, 0x6D, 0x93, 0x90, 0x60, 

  //Frame 7
  0x38, 0x44, 0x82, 0xE2, 0x92, 0x8A, 0xEC, 0xB8, 0x88, 0x18, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x0E, 0x35, 0x25, 0x26, 0x3F, 0x2F, 0x47, 0x41, 0x40, 0x21, 0x1E, 0x00
};
