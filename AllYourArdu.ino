#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
// #include <ArduboyTones.h>
#include "src/background.hpp"
#include "src/engine.hpp"
#include "src/sprites/Title.h"
#include "src/tones/squareztest.h"

Arduboy2 arduboy;
Engine engine;
Background background;
// ArduboyTones sound(arduboy.audio.enabled);

ArduboyPlaytune tunes(arduboy.audio.enabled);

// Playtune bytestream for file "midi/squareztest.mid" created by MIDI2TONES V1.0.0 on Thu Dec 14 00:32:38 2023
// command line: midi2tones -o1 midi/squareztest

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();

    engine.ship.arduboy = &arduboy;
    tunes.initChannel(PIN_SPEAKER_1);
    tunes.initChannel(PIN_SPEAKER_2);
    //  engine.enemies.sound = &sound;
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
            arduboy.audio.on();
            if (!tunes.playing()) {
                tunes.playScore(score);
            }
            return;
        }
        break;

    case GameState::GAME:
        if (!tunes.playing()) {
            tunes.playScore(score);
        }
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
