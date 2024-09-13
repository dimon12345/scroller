#include "Bomber.h"

USING_NS_CC;

cocos2d::Node* Bomber::create(const cocos2d::Size& visibleSize)
{
	_visibleSize = visibleSize;

	_sprite = Sprite::create("world\\bomber.png");
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, 0);
	_sprite->setTag(44);
	createCirclePhysicsBody(0.3f, 0xff, 0xf8);
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