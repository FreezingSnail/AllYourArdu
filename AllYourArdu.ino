#include "src/engine.hpp"
#include "src/sprites/Title.h"
#include <Arduboy2.h>

Arduboy2 arduboy;
Engine engine;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();

    engine.ship.arduboy = &arduboy;
}

void dbf loop() {
    if (!arduboy.nextFrame()) {
        return;
    }
    arduboy.clear();
    arduboy.pollButtons();

    switch (engine.state) {
    case GameState::TITLE:
        Sprites::drawOverwrite(0, 0, Title, 0);
        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::GAME;
            engine.ship.init();
            return;
        }
        break;

    case GameState::GAME:
        Arduboy2::setCursor(0, 0);
        arduboy.println(engine.enemies.score);
        engine.run();
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
        arduboy.println(engine.enemies.score);
        engine.restart();
        break;
    }

    arduboy.display();
}
