#include "Cloud.h"

#include "GameEngine.h"

USING_NS_CC;

#define CLOUD_VELOCITY 30

cocos2d::Node* Cloud::create() {
	_sprite = Sprite::create("world\\cloud.png");

	restartPosition(true);
	_velocity = Vec2(-CLOUD_VELOCITY, 0);
	return _sprite;
	
}

void Cloud::restartPosition(bool randomX)
{
	float cloudWidth = _sprite->getContentSize().width;
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	float x = visibleSize.width + cloudWidth / 2.f;
	if (randomX) {
		x = random(-cloudWidth/2, x);
	}

	_position = Vec2 (
		x,
		random(0.f, visibleSize.height)
	);
	_sprite->setPosition(_position);
}

void Cloud::update(float dt) {
	auto endX = 0 - _sprite->getContentSize().width / 2.f;
	_position += _velocity * dt;
	if (_position.x < endX) {
		restartPosition(false);
	}
	else {
		_sprite->setPosition(_position);
	}
}
