#include "Bird.h"

#include "CollisionBitmask.h"
#include "GameEngine.h"
#include "GameSettings.h"

USING_NS_CC;

cocos2d::Node* Bird:: create() {

	_sprite = Sprite::create("world\\bird.png");
	createCirclePhysicsBody(
		0.5f,
		CollisionBitmask::BIRD,
		CollisionBitmask::FIGHTER
	);
	reset();
	return _sprite;
}

void Bird::update(float dt)
{
	_changeDirectionTime -= dt;
	if (_changeDirectionTime <= 0) {
		_changeDirectionTime = random(BIRD_MIN_TIME_CHANGE_DIRECTION, BIRD_MAX_TIME_CHANGE_DIRECTION);
		int direction = rand() % 2 ? -1 : 1;

		float xVelocity = random(BIRD_X_MAX_VELOCITY, BIRD_X_MIN_VELOCITY);
		_velocity = Vec2(xVelocity, direction * BIRD_Y_VELOCITY);
	}

	_position += _velocity * dt;
	if (_position.y >= _maxHeight) {
		_velocity.y = -_velocity.y;
		_position = Vec2(_position.x, _maxHeight);
	}

	if (_position.y <= _minHeight) {
		_velocity.y = -_velocity.y;
		_position = Vec2(_position.x, _minHeight);
	}

	_sprite->setPosition(_position);
}

bool Bird::isVisible()
{
	if (_position.x + _sprite->getContentSize().width / 2.f < 0) {
		return false;
	}

	return true;
}

void Bird::reset() {
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	float randomHeight = visibleSize.height * random( BIRD_MIN_HEIGHT, BIRD_MAX_HEIGHT);

	_position = Vec2(visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_sprite->setPosition(_position);
	_changeDirectionTime = 0;

	_minHeight = visibleSize.height * BIRD_MIN_HEIGHT;
	_maxHeight = visibleSize.height * BIRD_MAX_HEIGHT;
}
