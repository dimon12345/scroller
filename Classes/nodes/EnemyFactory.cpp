#include "EnemyFactory.h"

#include "enemies/Bird.h"
#include "enemies/FastBomber.h"

Enemy* EnemyFactory::createEnemy() {
	return new FastBomber();
	//return new Bird();
}