#pragma once

#include "nodes/Enemy.h"

struct GameState {
	std::list<std::shared_ptr<Enemy>> enemies;
	bool gameOver = false;
	float nextEnemyTime = 0;
	float nextTimeAddEnemy = 0;
	size_t maxEnemies;
};
