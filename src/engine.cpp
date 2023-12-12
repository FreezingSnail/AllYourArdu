#include "engine.hpp"

Engine::Engine() {
    ship.playerBullets = playerBullets;
    enemies.playerBullets = playerBullets;
    state = GameState::TITLE;
    ship.enemies = enemies.enemies;
    ship.state = &state;
    ship.powerup = &enemies.powerups;
    loadLevel(0);
}

void Engine::run() {
    ticker++;
    debug = currentLevel->waves[currentSpawnIndex].spawnInstructions->type;
    if (ticker == currentLevel->waves[currentSpawnIndex].waitTicks) {
        ticker = 0;
        currentSpawnIndex++;
        spawnCounter = 0;
        if (currentLevel->waves[currentSpawnIndex].spawnInstructions->type == EnemyType::NONE) {
            currentLevelIndex++;
            loadLevel(currentLevelIndex);
            return;
        }
    }
    spawn();
    ship.run();
    enemies.tick();
}

void Engine::restart() {
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
}

void Engine::loadLevel(uint8_t level) {
    currentLevel = levels[level];
    ticker = 0;
    currentSpawnIndex = 0;
}

void dbf Engine::spawn() {
    uint16_t wait = currentLevel->waves[currentSpawnIndex].spawnInstructions->tickInterval;
    uint8_t total = currentLevel->waves[currentSpawnIndex].spawnInstructions->count;
    if (ticker % wait == 0 && spawnCounter < total) {

        enemies.spawn(currentLevel->waves[currentSpawnIndex].spawnInstructions->type, currentLevel->waves[currentSpawnIndex].x,
                      currentLevel->waves[currentSpawnIndex].y);
        spawnCounter++;
    }
}