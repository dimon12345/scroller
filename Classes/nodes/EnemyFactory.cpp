#include "EnemyFactory.h"

#include "enemies/Bird.h"
#include "enemies/FastBomber.h"

USING_NS_CC;

Enemy* EnemyFactory::createEnemy() {
	float rnd = random(0.0f, 1.f);

	if (rnd < 0.5f) {
		return new FastBomber();
	}
	else {
		return new Bird();
	}
}