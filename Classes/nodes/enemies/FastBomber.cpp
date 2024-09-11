#include "FastBomber.h"

#define BOMBER_FAST_MAX_HEIGHT 1.f
#define BOMBER_FAST_MIN_HEIGHT 0.8f
#define BOMBER_FAST_VELOCITY -200.f

USING_NS_CC;

void FastBomber::reset()
{
	float randomHeight = _visibleSize.height * random(BOMBER_FAST_MIN_HEIGHT, BOMBER_FAST_MAX_HEIGHT);
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(BOMBER_FAST_VELOCITY, 0);
}
