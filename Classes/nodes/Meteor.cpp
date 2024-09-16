#include "Meteor.h"

#include "CollisionBitmask.h"
#include "GameEngine.h"
#include "GameSettings.h"

USING_NS_CC;

cocos2d::Node* Meteor::create()
{
	_sprite = Sprite::create("world\\meteor.png");
	createCirclePhysicsBody(
		0.4f,
		CollisionBitmask::METEOR,
		CollisionBitmask::BOMBER | CollisionBitmask::INTERCEPTOR | CollisionBitmask::FIGHTER
	);
	_size = _sprite->getContentSize();
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	_velocity = Vec2(METEOR_X_VELOCITY, METEOR_Y_VELOCITY);
	_position = Vec2(visibleSize.width / 2, visibleSize.height + _sprite->getContentSize().height / 2);
	_sprite->setPosition(_position);
	restart();
	_visible = false;
	return _sprite;
}

void Meteor::restart()
{
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	_position = Vec2(visibleSize.width / 2 + random(0.f, visibleSize.width), visibleSize.height + _sprite->getContentSize().height / 2);
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

	if (_position.y < GameEngine::getInstance().gameState.landHeight - _size.height / 2) {
		return false;
	}

	return true;
}

void Meteor::hide()
{
	_visible = false;
	_position = Vec2(-_size.width / 2, GameEngine::getInstance().gameState.landHeight - _size.height / 2);
	_sprite->setPosition(_position);
}

