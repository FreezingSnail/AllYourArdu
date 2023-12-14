#include "src/background.hpp"
#include "src/engine.hpp"
#include "src/sprites/Title.h"
#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
Engine engine;
Background background;
// ArduboyPlaytune tunes(arduboy.audio.enabled);
ArduboyTones sound(arduboy.audio.enabled);

const byte score[] PROGMEM = {
    //
    0x90, 28,   0,  250, 0x91, 34,   0x80, 0,    250,  0x91, 33,  0,    250,  0x91, 33, 0,   250,  0x91, 36, 0,   250,  0x91, 34, 0,
    250,  0x91, 33, 0,   250,  0x90, 28,   0x91, 36,   0,    250, 0x90, 28,   0x81, 0,  250, 0x90, 55,   0,  250, 0x90, 54,   0,  250,
    0x90, 53,   0,  250, 0x90, 52,   0,    250,  0x90, 51,   0,   250,  0x90, 50,   0,  250, 0x90, 49,   0,  250, 0x80, 0xf0};

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();

    engine.ship.arduboy = &arduboy;
    //    tunes.initChannel(PIN_SPEAKER_1);
    // tunes.initChannel(PIN_SPEAKER_2);
    engine.enemies.sound = &sound;
    background.init();
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }
    arduboy.clear();
    arduboy.pollButtons();
    background.tick();

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
