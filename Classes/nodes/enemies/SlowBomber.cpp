#include "SlowBomber.h"

#define BOMBER_SLOW_MAX_HEIGHT 0.7f
#define BOMBER_SLOW_MIN_HEIGHT 0.4f
#define BOMBER_SLOW_VELOCITY -70.f

USING_NS_CC;

void SlowBomber::reset()
{
	float randomHeight = _visibleSize.height * random(BOMBER_SLOW_MIN_HEIGHT, BOMBER_SLOW_MAX_HEIGHT);
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(BOMBER_SLOW_VELOCITY, 0);
}
