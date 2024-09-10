#include "EnemyFactory.h"

#include "enemies/Bird.h"

Enemy* EnemyFactory::createEnemy() {
	return new Bird();
}