#pragma once

#include <list>
#include <memory>

#include "cocos2d.h"

class Enemy;
class EnemyBullet;
class Bullet;

struct GameState {
	std::list<std::shared_ptr<Enemy>> enemies;
	std::list<std::shared_ptr<EnemyBullet>> enemyBullets;
	std::list<std::shared_ptr<Bullet>> bullets;
	bool gameOver = false;
	float nextEnemyTime = 0;
	float nextTimeAddEnemy = 0;
	size_t maxEnemies;
	int score = 0;
	float landHeight = 0;
	cocos2d::Size visibleSize;
};
