#include "EnemyFactory.h"

#include "enemies/Bird.h"
#include "enemies/FastBomber.h"
#include "enemies/SlowBomber.h"

USING_NS_CC;

Enemy* EnemyFactory::createEnemy() {
	float rnd = random(0.0f, 1.f);

	if (rnd < 0.33f) {
		return new FastBomber();
	} else if (rnd < 0.66f) {
		return new SlowBomber();
	}
	else {
		return new Bird();
	}
}