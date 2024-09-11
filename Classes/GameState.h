#pragma once

#include <list>
#include <memory>

class Enemy;

struct GameState {
	std::list<std::shared_ptr<Enemy>> enemies;
	bool gameOver = false;
	float nextEnemyTime = 0;
	float nextTimeAddEnemy = 0;
	size_t maxEnemies;
};
