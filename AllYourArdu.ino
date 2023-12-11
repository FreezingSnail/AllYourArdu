#include "src/enemies.hpp"
#include "src/gamestate.hpp"
#include "src/globals.hpp"
#include "src/ship.hpp"
#include "src/sprites/Title.h"
#include <Arduboy2.h>

Arduboy2 arduboy;
Bullet playerBullets[BULLETCOUNT];
Ship ship;
Enemies enemies;
GameState state;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(120);
  arduboy.initRandomSeed();
  ship.playerBullets = playerBullets;
  enemies.playerBullets = playerBullets;
  state = GameState::TITLE;
  ship.enemies = enemies.enemies;
  ship.state = &state;
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.clear();
  arduboy.pollButtons();

  switch (state) {
  case GameState::TITLE:
    Sprites::drawOverwrite(0, 0, Title, 0);
    if (Arduboy2::justPressed(A_BUTTON)) {
      state = GameState::GAME;
    }
    break;
  case GameState::GAME:
    Arduboy2::setCursor(0, 0);
    arduboy.println(enemies.score);

    ship.run();
    enemies.tick();
    break;

  case GameState::LOSE:
    Arduboy2::setCursor(30, 20);
    arduboy.println(F("ALL YOUR ARDU"));
    Arduboy2::setCursor(40, 30);
    arduboy.println(F("ARE BELONG"));
    Arduboy2::setCursor(50, 40);
    arduboy.println(F("TO US"));
    Arduboy2::setCursor(30, 50);
    arduboy.print(F("SCORE: "));
    arduboy.println(enemies.score);
    if (Arduboy2::justPressed(A_BUTTON)) {
      state = GameState::TITLE;
      for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        playerBullets[i].active = false;
      }
      for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies.enemies[i].active = false;
      }
      enemies.score = 0;
    }
    break;
  }

  arduboy.display();
}
