#include "Bullet.h"

USING_NS_CC;

#define BULLET_X_VELOCITY 150.f

Node* Bullet::create(const cocos2d::Size& visibleSize, const Vec2 &position)
{
    _visibleSize = visibleSize;
    _position = position;
    _velocity = Vec2(BULLET_X_VELOCITY, 0);

    _sprite = Sprite::create("world\\bullet.png");
    _sprite->setPosition(position);
    createCirclePhysicsBody(0.5f, 0xf0, 0x4);
    return _sprite;
}

void Bullet::update(float dt)
{
    _velocity += Vec2(0, -30.f * dt);
    _position.add(Vec2(_velocity) * dt);
    _sprite->setPosition(_position);
}

bool Bullet::isVisible()
{
    if (_position.y < 0 - _sprite->getContentSize().height / 2.f) {
        return false;
    }

    if (_position.x > _visibleSize.width + _sprite->getContentSize().width / 2.f) {
        return false;
    }

    return true;
}
