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
  }
  arduboy.display();
}
