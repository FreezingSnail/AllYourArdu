#include "engine.hpp"
#include "lib/bossdata.hpp"

static bool isBoss(EnemyType type) {
    switch (type) {
    case EnemyType::BOSS_FRONT:
    case EnemyType::BOSS_MIDDLE:
    case EnemyType::BOSS_BACK:
    case EnemyType::BOSSCORELONG:
    case EnemyType::BOSSCORE:
    case EnemyType::BOSS_BOTTOM_WING:
    case EnemyType::BOSS_TOP_WING:
    case EnemyType::BOSS_CORE:
        return true;
    }
    return false;
}

Engine::Engine() {
    ship.playerBullets = playerBullets;
    enemies.playerBullets = playerBullets;
    state = GameState::TITLE;
    enemies.powerups.active = false;
    ship.enemies = enemies.enemies;
    ship.state = &state;
    ship.powerup = &enemies.powerups;
    loadLevel(0);
    // boss.load(&boss2Data);
}

void Engine::run() {
    ticker++;
    if (ticker >= pgm_read_word(&(currentLevel->waves[currentSpawnIndex]).waitTicks) && clearedEnemies()) {
        ticker = 0;
        currentSpawnIndex++;
        spawnCounter = 0;
        if (EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)) ==
            EnemyType::BOSS_CORE) {
            boss.load(&boss1Data);
        }
        if (EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)) ==
            EnemyType::BOSSCORELONG) {
            boss.load(&boss2Data);
        }
    }
    if (EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type)) == EnemyType::NONE &&
        clearedEnemies()) {
        currentLevelIndex++;
        if (currentLevelIndex == 10) {
            state = GameState::WIN;
            return;
        }
        state = GameState::LEVELPAUSE;
        loadLevel(currentLevelIndex);
        return;
    }

    spawn();
    ship.run();
    enemies.tick();
    bulletTick();
    if (boss.active) {
        boss.tick(enemyBullets);
        for (uint8_t i = 0; i < 8; i++) {
            explosions[i].tick();
        }

        for (uint8_t j = 0; j < BULLETCOUNT; j++) {

            int8_t hit = boss.hit(playerBullets[j].getBounding());
            if (hit >= 0) {
                boss.enemies[hit].takeDamage(playerBullets[j].getDamage());
                spawnExplode(playerBullets[j].x - 4, playerBullets[j].y - 4, 8);
                playerBullets[j].reset();

                break;
            }
        }
    }

    for (uint8_t i = 0; i < ENEMIES; i++) {
        if (!enemies.enemies[i].active) {
            continue;
        }

        enemies.enemies[i].tick(enemyBullets);

        if (ship.getBound().overlap(enemies.enemies[i].getCollision())) {
            ship.hp--;
            ship.x -= 5;
            ship.subx -= 20;
            if (hitable(enemies.enemies[i].type)) {
                enemies.enemies[i].reset();
            }
            if (ship.hp <= 0) {
                state = GameState::LOSE;
            }
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
                    spawnExplode(playerBullets[j].x - 4, playerBullets[j].y - 4, 0);

                    if (enemies.enemies[i].takeDamage(playerBullets[j].getDamage())) {
                        enemies.powerUpSpawn(enemies.enemies[i].x, enemies.enemies[i].y);
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

    for (uint8_t i = 0; i < 6; i++) {
        if (!boss.enemies[i].active) {
            continue;
        }
        if (ship.getBound().overlap(boss.enemies[i].getCollision())) {
            ship.hp--;
            enemies.enemies[i].reset();
            if (ship.hp <= 0) {
                state = GameState::LOSE;
            }
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

void Engine::restart() {
    currentSpawnIndex = 0;
    spawnCounter = 0;
    currentLevelIndex = 0;
    boss.active = false;
    ship.init();
    // ship.init();
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        playerBullets[i].active = false;
    }
    for (uint8_t i = 0; i < ENEMIES; i++) {
        enemies.enemies[i].active = false;
    }
    for (uint8_t i = 0; i < 6; i++) {
        boss.enemies[i].active = false;
    }
    enemies.score = 0;
}

void Engine::loadLevel(uint8_t level) {
    currentLevel = pgm_read_pointer(&levels[level]);
    boss.active = false;
    ticker = 0;
    currentSpawnIndex = 0;
}

void Engine::spawn() {
    EnemyType t = EnemyType(pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->type));
    if (isBoss(t)) {
        return;
    }
    uint16_t wait = pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->tickInterval);
    uint8_t total = pgm_read_byte(&pgm_read_pointer(&currentLevel->waves[currentSpawnIndex].spawnInstructions)->count);
    if (ticker % wait == 0 && spawnCounter < total) {

        enemies.spawn(t, pgm_read_byte(&currentLevel->waves[currentSpawnIndex].x),
                      pgm_read_byte(&currentLevel->waves[currentSpawnIndex].y));
        spawnCounter++;
    }
}

void Engine::bulletTick() {
    for (uint8_t i = 0; i < BULLETCOUNT; i++) {
        enemyBullets[i].tick();

        if (enemyBullets[i].getBounding().overlap(ship.getBound())) {
            ship.hp--;
            enemies.enemies[i].reset();
            if (ship.hp <= 0) {
                state = GameState::LOSE;
            }
            enemyBullets[i].reset();
        } else if (ship.lilShips[0].active && enemyBullets[i].getBounding().overlap(ship.lilShips[0].getBound())) {
            ship.lilShips[0].despawn();
            enemyBullets[i].reset();
            // spawnExplode(enemyBullets[i].x - 4, enemyBullets[i].y - 4, 8);
        } else if (ship.lilShips[1].active && enemyBullets[i].getBounding().overlap(ship.lilShips[1].getBound())) {
            ship.lilShips[1].despawn();
            enemyBullets[i].reset();
            // spawnExplode(enemyBullets[i].x - 4, enemyBullets[i].y - 4, 8);
        }
    }
}

bool Engine::clearedEnemies() {
    if (!boss.active) {
        for (uint8_t i = 0; i < ENEMIES; i++) {
            if (enemies.enemies[i].active) {
                return false;
            }
        }
    } else {
        return !boss.bossActive();
    }

    return true;
}

void Engine::spawnExplode(uint8_t x, uint8_t y, uint8_t size) {
    uint8_t spawn = rand() % 100;
    if (spawn < 75) {
        return;
    }
    for (uint8_t i = 0; i < 8; i++) {
        if (!explosions[i].active) {
            if (size == 0) {
                size = ((rand() % 2) == 0) ? 8 : 16;
            }
            explosions[i].spawn(x, y, size);
            return;
        }
    }
}

bool hitDie(EnemyType t) {
    switch (t) {
    case EnemyType::WALL:
    case EnemyType::BROKEN_WALL_TOP:
    case EnemyType::BROKEN_WALL_BOTTOM:
    case EnemyType::BOSSCORE:
    case EnemyType::BOSSCORELONG:
    case EnemyType::BOSS_FRONT:
    case EnemyType::BOSS_MIDDLE:
    case EnemyType::BOSS_BACK:
    case EnemyType::BOSS_BOTTOM_WING:
    case EnemyType::BOSS_TOP_WING:
    case EnemyType::CARRIER:
        return false;
    }
    return true;
}