#include "engine.hpp"
#include "lib/bossdata.hpp"

Engine::Engine() {
    ship.playerBullets = playerBullets;
    enemies.playerBullets = playerBullets;
    state = GameState::TITLE;
    ship.enemies = enemies.enemies;
    ship.state = &state;
    ship.powerup = &enemies.powerups;
    loadLevel(0);
    boss.load(&boss1Data);
}

void Engine::run() {
    ticker++;
    if (ticker == pgm_read_word(&(currentLevel->waves[currentSpawnIndex]).waitTicks)) {
        ticker = 0;
        currentSpawnIndex++;
        spawnCounter = 0;
        if (EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)) ==
            EnemyType::BOSS_CORE) {
            boss.load(&boss1Data);
        }
    }
    if (EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)) == EnemyType::NONE &&
        clearedEnemies()) {
        currentLevelIndex++;
        loadLevel(currentLevelIndex);
        return;
    }

    spawn();
    ship.run();
    enemies.tick();
    bulletTick();
    boss.tick(enemyBullets);

    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies.enemies[i].active) {
            continue;
        }

        enemies.enemies[i].tick(enemyBullets);

        if (ship.getBound().overlap(enemies.enemies[i].getCollision())) {
            //*state = GameState::LOSE;
        }

        if (ship.lilShips[0].active && enemies.enemies[i].hit(ship.lilShips[0].getBound())) {
            ship.lilShips[0].despawn();
            // enemies.enemies[i].takeDamage(-5);
        }

        if (ship.lilShips[1].active && enemies.enemies[i].hit(ship.lilShips[1].getBound())) {
            ship.lilShips[1].despawn();
            // enemies.enemies[i].takeDamage(-5);
        }

        for (uint8_t j = 0; j < BULLETCOUNT; j++) {
            if (playerBullets[j].active) {
                if (enemies.enemies[i].hit(playerBullets[j].getBounding())) {
                    if (enemies.enemies[i].takeDamage(playerBullets[j].getDamage())) {
                        // enemies.sound->tone(NOTE_E3, 40);
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
    if (boss.active) {
        for (uint8_t j = 0; j < BULLETCOUNT; j++) {

            int8_t hit = boss.hit(playerBullets[j].getBounding());
            if (hit >= 0) {
                boss.enemies[hit].takeDamage(playerBullets[j].getDamage());
                playerBullets[j].reset();
                break;
            }
        }

        for (uint8_t i = 0; i < 6; i++) {
            if (!boss.enemies[i].active) {
                continue;
            }
            if (ship.getBound().overlap(boss.enemies[i].getCollision())) {
                //*state = GameState::LOSE;
            }

            if (ship.lilShips[0].active && boss.enemies[i].hit(ship.lilShips[0].getBound())) {
                ship.lilShips[0].despawn();
                // enemies.enemies[i].takeDamage(-5);
            }

            if (ship.lilShips[1].active && boss.enemies[i].hit(ship.lilShips[1].getBound())) {
                ship.lilShips[1].despawn();
                // enemies.enemies[i].takeDamage(-5);
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
    currentLevel = pgm_read_pointer(&levels[level]);
    ticker = 0;
    currentSpawnIndex = 0;
}

void Engine::spawn() {
    uint16_t wait = pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->tickInterval);
    uint8_t total = pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->count);
    if (ticker % wait == 0 && spawnCounter < total) {
        debug = total;

        enemies.spawn(EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)),
                      pgm_read_byte(&currentLevel->waves[currentSpawnIndex].x), pgm_read_byte(&currentLevel->waves[currentSpawnIndex].y));
        spawnCounter++;
    }
}

void Engine::bulletTick() {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        enemyBullets[i].tick();

        if (enemyBullets[i].getBounding().overlap(ship.getBound())) {
            // player hit
            enemyBullets[i].reset();
        } else if (ship.lilShips[0].active && enemyBullets[i].getBounding().overlap(ship.lilShips[0].getBound())) {
            ship.lilShips[0].despawn();
            enemyBullets[i].reset();
        } else if (ship.lilShips[0].active && enemyBullets[i].getBounding().overlap(ship.lilShips[1].getBound())) {
            ship.lilShips[1].despawn();
            enemyBullets[i].reset();
        }
    }
}

bool Engine::clearedEnemies() {
    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (enemies.enemies[i].active) {
            return false;
        }
    }

    return true;
}