#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
// #include <ArduboyTones.h>
#include "src/background.hpp"
#include "src/engine.hpp"
#include "src/sprites/TitleText.h"
#include "src/sprites/Cat.h"
#include "src/tones/squareztest.h"
#include "src/sprites/snailware.h"

bool sound;
Arduboy2 arduboy;
Engine engine;
Background background;
// ArduboyTones sound(arduboy.audio.enabled);
uint16_t ticker;
uint8_t frame;
uint8_t cheat;
int8_t menuPage = 0;

ArduboyPlaytune tunes(arduboy.audio.enabled);

// Playtune bytestream for file "midi/squareztest.mid" created by MIDI2TONES V1.0.0 on Thu Dec 14 00:32:38 2023
// command line: midi2tones -o1 midi/squareztest
void spawnTitleSplode(uint8_t x, uint8_t y) {
    for (uint8_t i = 0; i < 8; i++) {
        if (!engine.explosions[i].active) {
            engine.explosions[i].spawn(x, y, 8);
            return;
        }
    }
}
void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();

    engine.ship.arduboy = &arduboy;
    engine.ship.init();
    tunes.initChannel(PIN_SPEAKER_1);
    tunes.initChannel(PIN_SPEAKER_2);
    //  engine.enemies.sound = &sound;
    background.init();
    ticker = 0;
    frame = 0;
    engine.state = GameState::SPLASH;
    sound = false;
}

void intro() {
    ticker++;

    if (ticker % 5 == 0) {
        frame++;
    }
    for (uint8_t i = 0; i < 8; i++) {
        engine.explosions[i].tick();
    }

    if (ticker == 60) {
        spawnTitleSplode(20, 10);
    } else if (ticker == 70) {
        spawnTitleSplode(60, 50);
    } else if (ticker == 90) {
        spawnTitleSplode(40, 40);
    } else if (ticker == 105) {
        spawnTitleSplode(80, 35);
    } else if (ticker == 125) {
        spawnTitleSplode(35, 12);
    } else if (ticker == 130) {
        spawnTitleSplode(885, 45);
    } else if (ticker == 132) {
        spawnTitleSplode(49, 20);
    }

    if (ticker == 300) {
        engine.state = GameState::TITLE;
    }
}

void instructions() {
    if (arduboy.justPressed(B_BUTTON)) {
        engine.state = GameState::TITLE;
    }
    arduboy.setCursor(0, 0);

    if (menuPage == 0) {
        arduboy.println(F("A to shoot"));
        arduboy.println(F("B changes formation"));
        arduboy.println(F("A&B to pause"));
        arduboy.println(F("\x1B&\x1A uses powerups"));

        arduboy.setCursor(0, 55);
        arduboy.println(F("press \x19 for more"));
    } else if (menuPage == 1) {
        arduboy.println(F("powerups heal you"));
        arduboy.println(F("when picked up"));
        arduboy.println(F("\x18 toggles sound on"));
        arduboy.println(F("the title screen"));

        arduboy.setCursor(0, 55);
        arduboy.println(F("press \x18 or \x19 for more"));
    } else {
        arduboy.println(F("try hitting left on"));
        arduboy.println(F("the menu a few times"));
        arduboy.println(F("if it's too hard"));
        arduboy.println(F("You'll see a change"));
        arduboy.println(F("maybe there's more..."));

        arduboy.setCursor(0, 55);
        arduboy.println(F("press \x18 for more"));
    }

    if (arduboy.justPressed(UP_BUTTON)) {
        menuPage--;
        if (menuPage < 0) {
            menuPage = 0;
        }
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
        menuPage++;
        if (menuPage > 2) {
            menuPage = 2;
        }
    }
}

void loop() {
    if (!arduboy.nextFrame()) {
        return;
    }

    arduboy.clear();
    arduboy.pollButtons();
    background.tick();

    switch (engine.state) {
    case GameState::SPLASH:
        ticker++;
        Sprites::drawOverwrite(32, 0, snailware, 0);
        Arduboy2::setCursor(5, 10);
        arduboy.println(F("SNAIL"));
        Arduboy2::setCursor(32 + 60, 10);
        arduboy.println(F("WARE"));
        if (Arduboy2::justPressed(A_BUTTON) || ticker > 180) {
            ticker = 0;
            engine.state = GameState::OPENING;
        }
        break;
    case GameState::OPENING:
        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::TITLE;
        }

        intro();
        break;
    case GameState::TITLE:
        Sprites::drawOverwrite(44, -2, Cat, 0);
        Sprites::drawSelfMasked(0, 0, TitleText, 0);
        Sprites::drawSelfMasked(81, 0, TitleText, 1);

        Arduboy2::setCursor(0, 55);
        arduboy.print(F("B for help "));
        Arduboy2::setCursor(85, 55);
        arduboy.print(F("sound:"));
        if (sound) {
            arduboy.print(F("+"));
        } else {
            arduboy.print(F("-"));
        }
        if (cheat >= 5 && cheat < 25) {
            Arduboy2::setCursor(118, 5);
            arduboy.print(F("\x02"));
        } else if (cheat >= 25) {
            Arduboy2::setCursor(118, 5);
            arduboy.print(F("\x2a"));
        }
        if (Arduboy2::justPressed(UP_BUTTON)) {
            sound = !sound;
        }
        arduboy.audio.on();
        if (!tunes.playing() && sound) {
            tunes.playScore(score);
        } else if (tunes.playing() && !sound) {
            tunes.stopScore();
        }
        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::LEVELPAUSE;
            return;
        }
        if (Arduboy2::justPressed(B_BUTTON)) {
            engine.state = GameState::INSTRUCTIONS;
            return;
        }
        if (Arduboy2::justPressed(LEFT_BUTTON)) {
            cheat++;
            if (cheat == 5) {
                engine.ship.hp = 50;
            }
            if (cheat == 25) {
                engine.ship.hp = 200;
            }
        }
        break;

    case GameState::GAME:
        if (!tunes.playing() && sound) {
            tunes.playScore(score);
        }
        if (Arduboy2::justPressed(A_BUTTON) && Arduboy2::justPressed(B_BUTTON)) {
            engine.state = GameState::LEVELPAUSE;
        }
        Arduboy2::setCursor(0, 0);
        arduboy.print(F("S:"));
        arduboy.print(engine.enemies.score);
        Arduboy2::setCursor(93, 0);
        arduboy.print(F("HP:"));
        arduboy.print(engine.ship.hp);
        engine.run();
        break;

    case GameState::LEVELPAUSE:
        Arduboy2::setCursor(30, 30);
        arduboy.print(F("LEVEL: "));
        arduboy.println(engine.currentLevelIndex + 1);
        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::GAME;
        }
        break;

    case GameState::LOSE:
        Arduboy2::setCursor(30, 10);
        arduboy.println(F("ALL YOUR ARDU"));
        Arduboy2::setCursor(40, 20);
        arduboy.println(F("ARE BELONG"));
        Arduboy2::setCursor(50, 30);
        arduboy.println(F("TO US"));
        Arduboy2::setCursor(30, 40);
        arduboy.print(F("SCORE: "));
        arduboy.println(engine.enemies.score);
        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::TITLE;
            engine.restart();
        }
        break;
    case GameState::WIN:
        Arduboy2::setCursor(30, 10);
        arduboy.println(F("ALL YOUR ARDU"));
        Arduboy2::setCursor(40, 20);
        arduboy.println(F("ARE BELONG"));
        Arduboy2::setCursor(20, 30);
        arduboy.println(F("TO YOU, CONGRATS"));
        Arduboy2::setCursor(30, 40);
        arduboy.print(F("SCORE: "));
        arduboy.println(engine.enemies.score);

        if (Arduboy2::justPressed(A_BUTTON)) {
            engine.state = GameState::TITLE;
            engine.restart();
        }
        break;
    case GameState::INSTRUCTIONS:
        instructions();
        break;
    }

    arduboy.display();
}
