#include "Bird.h"

USING_NS_CC;

#define BIRD_X_MAX_VELOCITY -160.f
#define BIRD_X_MIN_VELOCITY -130.f

#define BIRD_Y_VELOCITY 40.f
#define BIRD_MAX_HEIGHT 0.4f
#define BIRD_MIN_HEIGHT 0.1f
#define BIRD_MIN_TIME_CHANGE_DIRECTION 0.5f
#define BIRD_MAX_TIME_CHANGE_DIRECTION 3.0f

cocos2d::Node* Bird:: create(const cocos2d::Size& visibleSize) {
	_visibleSize = visibleSize;

	_birdSprite = Sprite::create("world\\bird.png");
	auto body = PhysicsBody::createBox(_birdSprite->getContentSize());
	body->setContactTestBitmask(0x1);
	body->setDynamic(false);
	_birdSprite->setPhysicsBody(body);
	reset();
	return _birdSprite;
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
	if (_position.y >= _visibleSize.height * BIRD_MAX_HEIGHT) {
		_velocity = Vec2(_velocity.x, -_velocity.y);
		_position = Vec2(_position.x, _visibleSize.height * BIRD_MAX_HEIGHT);
	}

	if (_position.y <= _visibleSize.height * BIRD_MIN_HEIGHT) {
		_velocity = Vec2(_velocity.x, -_velocity.y);
		_position = Vec2(_position.x, _visibleSize.height * BIRD_MIN_HEIGHT);
	}

	_birdSprite->setPosition(_position);
}

bool Bird::isVisible()
{
	if (_position.x + _birdSprite->getContentSize().width < 0) {
		return false;
	}

	return true;
}

void Bird::reset() {
	float randomHeight = _visibleSize.height * random( BIRD_MIN_HEIGHT, BIRD_MAX_HEIGHT);

	_position = Vec2(_visibleSize.width + _birdSprite->getContentSize().width / 2.f, randomHeight);
	_birdSprite->setPosition(_position);
	_changeDirectionTime = 0;
}
