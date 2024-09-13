#include "Meteor.h"

USING_NS_CC;

#define METEOR_X_VELOCITY -100.f
#define METEOR_Y_VELOCITY -100.f

cocos2d::Node* Meteor::create(const cocos2d::Size& visibleSize, float landHeight)
{
	_visibleSize = visibleSize;
	_landHeight = landHeight;
	_sprite = Sprite::create("world\\meteor.png");
	_size = _sprite->getContentSize();
	_velocity = Vec2(METEOR_X_VELOCITY, METEOR_Y_VELOCITY);
	_position = Vec2(_visibleSize.width / 2, _visibleSize.height + _sprite->getContentSize().height / 2);
	_sprite->setPosition(_position);
	restart();
	_visible = false;
	return _sprite;
}

void Meteor::restart()
{
	_position = Vec2(_visibleSize.width / 2 + random(0.f, _visibleSize.width), _visibleSize.height + _sprite->getContentSize().height / 2);
	_sprite->setPosition(_position);
	_visible = true;
}

void Meteor::update(float dt)
{
	if (!_visible) {
		return;
	}

	_position += _velocity * dt;
	_sprite->setPosition(_position);

	if (!checkVisibility()) {
		_visible = false;
	}
}

bool Meteor::checkVisibility()
{
	if (_position.x < -_size.width / 2) {
		return false;
	}

	if (_position.y < _landHeight-_size.height / 2) {
		return false;
	}

	return true;
}

