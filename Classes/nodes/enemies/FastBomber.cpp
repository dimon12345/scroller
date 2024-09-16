#include "FastBomber.h"

#include "GameEngine.h"
#include "GameSettings.h"

USING_NS_CC;

void FastBomber::reset()
{
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	float randomHeight = visibleSize.height * random(BOMBER_FAST_MIN_HEIGHT, BOMBER_FAST_MAX_HEIGHT);
	_position = Vec2(visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(BOMBER_FAST_VELOCITY, 0);
}
