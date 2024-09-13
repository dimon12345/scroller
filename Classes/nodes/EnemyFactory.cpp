#include "EnemyFactory.h"

#include "enemies/Bird.h"
#include "enemies/FastBomber.h"
#include "enemies/SlowBomber.h"
#include "enemies/Interceptor.h"

USING_NS_CC;

Enemy* EnemyFactory::createEnemy() {
	float rnd = random(0.0f, 1.f);

	if (rnd < 0.25f) {
		return new FastBomber();
	} else if (rnd < 0.50f) {
		return new SlowBomber();
	}
	else if (rnd < 0.75f) {
		return new Interceptor();
	}
	else {
		return new Bird();
	}
}