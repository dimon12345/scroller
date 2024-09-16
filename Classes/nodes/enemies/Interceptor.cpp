#include "Interceptor.h"

#include "GameEngine.h"
#include "nodes/EnemyBullet.h"
#include "nodes/Bullet.h"
#include "CollisionBitmask.h"

USING_NS_CC;

#define INTERCEPTOR_MIN_HEIGHT 0.15f
#define INTERCEPTOR_MAX_HEIGHT 0.9f
#define INTERCEPTOR_VELOCITY -300.f
#define INTERCEPTOR_Y_VELOCITY 200.f

#define INTERCEPTOR_FIRE_RATE 1.5f
#define BULLET_WIDTH 28.f
#define BULLET_HEIGHT 4.f

Interceptor::~Interceptor()
{
}
cocos2d::Node* Interceptor::create()
{
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	_sprite = Sprite::create("world\\interceptor.png");
	_position = Vec2(visibleSize.width + _sprite->getContentSize().width / 2.f, 0);
	_sprite->setTag(44);
	createCirclePhysicsBody(
		0.3f,
		CollisionBitmask::INTERCEPTOR,
		CollisionBitmask::FIGHTER | CollisionBitmask::METEOR | CollisionBitmask::BULLET
	);
	_nextShotTime = 0;
	_minHeight = visibleSize.height * INTERCEPTOR_MIN_HEIGHT;
	reset();
	return _sprite;
}

void Interceptor::update(float dt)
{
	if (!GameEngine::getInstance().gameState.bullets.empty()) {
		updateVerticalVelocity(dt);
	}
	else {
		_velocity.y = 0.f;
	}

	_position += _velocity * dt;
	if (_position.y < _minHeight) {
		_position.y = _minHeight;
	}
	_sprite->setPosition(_position);

	_nextShotTime -= dt;
	if (_nextShotTime < 0) {
		_nextShotTime = INTERCEPTOR_FIRE_RATE;
		fire();
	}
}

void Interceptor::updateVerticalVelocity(float dt)
{
	bool upSafe = true;
	bool downSafe = true;
	float nearestHeight = 0.f;
	float crashSizeHorizontal = 1 + _sprite->getContentSize().width / 2.f + BULLET_WIDTH / 2.f;

	const Size& interceptorSize = _sprite->getContentSize();
	float crashSizeVertical = interceptorSize.height / 2.f + BULLET_HEIGHT / 2.f;

	Vec2 nearestBullet = (*GameEngine::getInstance().gameState.bullets.begin())->getPosition();
	float nearestBulletDistance = nearestBullet.distance(_position);

	for (auto bullet : GameEngine::getInstance().gameState.bullets) {
		auto bulletPosition = bullet->getPosition();
		if (bulletPosition.x > _position.x - crashSizeHorizontal) {
			continue;
		}

		if (bulletPosition.x > _position.x - interceptorSize.width / 2.f) {

			float safeHeightTop = _position.y + interceptorSize.height / 2.f;
			if (
				(bulletPosition.y > safeHeightTop) &&
				(bulletPosition.y < safeHeightTop + INTERCEPTOR_Y_VELOCITY * dt)
				) {
				upSafe = false;
			}

			float safeHeightBottom = _position.y - interceptorSize.height / 2.f;
			if (
				(bulletPosition.y < safeHeightBottom) &&
				(bulletPosition.y > safeHeightTop - INTERCEPTOR_Y_VELOCITY * dt)
				) {
				downSafe = false;
			}
			continue;
		}

		float distance = bullet->getPosition().distance(_position);
		if (distance < nearestBulletDistance) {
			nearestBullet = bulletPosition;
			nearestBulletDistance = distance;
		}
	}

	if (nearestBulletDistance < interceptorSize.width) {
		float yVelocity = 0.f;
		if (upSafe && (nearestBullet.y < _position.y)) {
			yVelocity = INTERCEPTOR_Y_VELOCITY;
		}

		if (downSafe && (nearestBullet.y > _position.y)){
			yVelocity = -INTERCEPTOR_Y_VELOCITY;
		}

		_velocity = Vec2(_velocity.x, yVelocity);
	}
	else {
		_velocity = Vec2(_velocity.x, 0);
	}
}

void Interceptor::fire()
{
	auto bullet = std::make_shared<EnemyBullet>();
	auto bulletSprite = bullet->create(_position);
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
	const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
	float randomHeight = visibleSize.height * random(INTERCEPTOR_MIN_HEIGHT, INTERCEPTOR_MAX_HEIGHT);
	_position = Vec2(visibleSize.width + _sprite->getContentSize().width / 2.f, randomHeight);
	_velocity = Vec2(INTERCEPTOR_VELOCITY, 0);
}