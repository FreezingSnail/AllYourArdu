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
    bulletTick();

    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies.enemies[i].active) {
            continue;
        }

        enemies.enemies[i].tick(enemyBullets);

        if (ship.getBound().overlap(enemies.enemies[i].getCollision())) {
            //*state = GameState::LOSE;
        }

        if (ship.lilShips[0].getBound().overlap(enemies.enemies[i].getCollision())) {
            ship.lilShips[0].despawn();
        }

        if (ship.lilShips[1].getBound().overlap(enemies.enemies[i].getCollision())) {
            ship.lilShips[1].despawn();
        }

        for (uint8_t j = 0; j < BULLETCOUNT; j++) {
            if (playerBullets[j].active) {
                if (enemies.enemies[i].hit(playerBullets[j].getBounding())) {
                    if (enemies.enemies[i].takeDamage(playerBullets[j].getDamage())) {
                        enemies.sound->tone(NOTE_E3, 40);
                        enemies.score++;
                        if (enemies.enemies[i].type == EnemyType::WALL) {
                            // spawnBrokenWall(EnemyType::BROKEN_WALL_TOP, enemies[i].x, enemies[i].y, enemies[i].stepPointer,
                            // enemies[i].stepCount);

                            enemies.spawnBrokenWall(EnemyType::BROKEN_WALL_BOTTOM, enemies.enemies[i].x, enemies.enemies[i].y + 23,
                                                    enemies.enemies[i].stepCount, enemies.enemies[i].stepPointer);
                            enemies.spawnBrokenWall(EnemyType::BROKEN_WALL_TOP, enemies.enemies[i].x, -3, enemies.enemies[i].stepCount,
                                                    enemies.enemies[i].stepPointer);
                        }
                    }
                    playerBullets[j].reset();
                    break;
                }
            }
        }
    }
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

void Engine::bulletTick() {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        enemyBullets[i].tick();
    }
}