#include "Interceptor.h"

USING_NS_CC;

#define INTERCEPTOR_MIN_HEIGHT 0.1f
#define INTERCEPTOR_MAX_HEIGHT 0.9f
#define INTERCEPTOR_VELOCITY -300.f


cocos2d::Node* Interceptor::create(const cocos2d::Size& visibleSize)
{
	_visibleSize = visibleSize;

	_sprite = Sprite::create("world\\interceptor.png");
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, 0);
	_sprite->setTag(44);
	createCirclePhysicsBody(0.3f, 0xff, 0xf8);
	reset();
	return _sprite;
}

void Interceptor::update(float dt)
{
	_position += _velocity * dt;
	_sprite->setPosition(_position);
}

bool Interceptor::isVisible()
{
	if (_position.x + _sprite->getContentSize().width < 0) {
		return false;
	}

	return true;
}

void Interceptor::reset()
{
	float randomHeight = _visibleSize.height * random(INTERCEPTOR_MIN_HEIGHT, INTERCEPTOR_MAX_HEIGHT);
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(INTERCEPTOR_VELOCITY, 0);
}