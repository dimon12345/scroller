#include "Interceptor.h"

#include "GameEngine.h"
#include "nodes/EnemyBullet.h"
#include "CollisionBitmask.h"

USING_NS_CC;

#define INTERCEPTOR_MIN_HEIGHT 0.1f
#define INTERCEPTOR_MAX_HEIGHT 0.9f
#define INTERCEPTOR_VELOCITY -300.f

#define INTERCEPTOR_FIRE_RATE 1.5f

Interceptor::~Interceptor()
{
}
cocos2d::Node* Interceptor::create(const cocos2d::Size& visibleSize)
{
	_visibleSize = visibleSize;

	_sprite = Sprite::create("world\\interceptor.png");
	_position = Vec2(_visibleSize.width + _sprite->getContentSize().width / 2.f, 0);
	_sprite->setTag(44);
	createCirclePhysicsBody(
		0.3f,
		CollisionBitmask::INTERCEPTOR,
		CollisionBitmask::FIGHTER | CollisionBitmask::METEOR | CollisionBitmask::BULLET
	);
	_nextShotTime = 0;
	reset();
	return _sprite;
}

void Interceptor::update(float dt)
{
	_position += _velocity * dt;
	_sprite->setPosition(_position);

	_nextShotTime -= dt;
	if (_nextShotTime < 0) {
		_nextShotTime = INTERCEPTOR_FIRE_RATE;
		fire();
	}
}

void Interceptor::fire()
{
	auto bullet = std::make_shared<EnemyBullet>();
	auto bulletSprite = bullet->create(_visibleSize, _position);
	_sprite->getParent()->addChild(bulletSprite);

	GameEngine::getInstance().addEnemyBullet(bullet);
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