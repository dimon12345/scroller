#include "EnemyBullet.h"

USING_NS_CC;

#define BULLET_X_VELOCITY -450.f

#include "CollisionBitmask.h"

Node* EnemyBullet::create(const cocos2d::Size& visibleSize, const Vec2 &position)
{
    _visibleSize = visibleSize;
    _position = position;
    _velocity = Vec2(BULLET_X_VELOCITY, 0);

    _sprite = Sprite::create("world\\enemy_bullet.png");
    _sprite->setPosition(position);
    createCirclePhysicsBody(
        0.4f,
        CollisionBitmask::ENEMY_BULLET,
        CollisionBitmask::FIGHTER
    );
    return _sprite;
}

void EnemyBullet::update(float dt)
{
    _velocity += Vec2(0, -30.f * dt);
    _position += Vec2(_velocity) * dt;
    _sprite->setPosition(_position);
}

bool EnemyBullet::isVisible()
{
    if (_position.y < 0) {
        return false;
    }

    if (_position.x < -_sprite->getContentSize().width) {
        return false;
    }

    return true;
}
