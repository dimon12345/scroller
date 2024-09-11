#include "Bomber.h"

USING_NS_CC;

#define BOMBER_SLOW_MAX_HEIGHT 7.f
#define BOMBER_SLOW_MIN_HEIGHT 0.4f
#define BOMBER_SLOW_VELOCITY 100.f

cocos2d::Node* Bomber::create(const cocos2d::Size& visibleSize)
{
	_visibleSize = visibleSize;

	_sprite = Sprite::create("world\\bomber.png");
	auto body = PhysicsBody::createBox(_sprite->getContentSize());
	body->setContactTestBitmask(0x2);
	body->setDynamic(false);
	_sprite->setPhysicsBody(body);
	reset();
	return _sprite;

}

void Bomber::update(float dt)
{
	_position += _velocity * dt;
	_sprite->setPosition(_position);
}

bool Bomber::isVisible()
{
	if (_position.x + _sprite->getContentSize().width < 0) {
		return false;
	}

	return true;
}
/*
void Bomber::reset()
{
	if (rand() % 2) {
	}
	else {
		float randomHeight = _visibleSize.height * random(BOMBER_SLOW_MIN_HEIGHT, BOMBER_SLOW_MAX_HEIGHT);
		_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
		_velocity = Vec2(BOMBER_SLOW_VELOCITY, 0);
	}

	_sprite->setPosition(_position);
}
*/