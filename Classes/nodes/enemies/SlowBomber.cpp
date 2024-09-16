#include "SlowBomber.h"

#include "GameEngine.h"
#include "GameSettings.h"

USING_NS_CC;

void SlowBomber::reset()
{
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	float randomHeight = visibleSize.height * random(BOMBER_SLOW_MIN_HEIGHT, BOMBER_SLOW_MAX_HEIGHT);
	_position = Vec2(visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(BOMBER_SLOW_VELOCITY, 0);
}
