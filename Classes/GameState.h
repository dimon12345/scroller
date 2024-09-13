#pragma once

#include <list>
#include <memory>

class Enemy;
class EnemyBullet;

namespace cocos2x { class Node; }

struct GameState {
	std::list<std::shared_ptr<Enemy>> enemies;
	std::list<std::shared_ptr<EnemyBullet>> enemyBullets;
	bool gameOver = false;
	float nextEnemyTime = 0;
	float nextTimeAddEnemy = 0;
	size_t maxEnemies;
	int score = 0;
	float landHeight = 0;
};
