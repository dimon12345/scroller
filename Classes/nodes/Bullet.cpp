#include "Bullet.h"

#include "CollisionBitmask.h"
#include "GameEngine.h"
#include "GameSettings.h"

USING_NS_CC;

Node* Bullet::create(const Vec2 &position, float landHeight)
{
    _position = position;
    _velocity = Vec2(BULLET_X_VELOCITY, 0);
    _landHeight = landHeight;

    _sprite = Sprite::create("world\\bullet.png");
    _sprite->setPosition(position);
    createCirclePhysicsBody(
        0.4f,
        CollisionBitmask::BULLET,
        CollisionBitmask::BOMBER | CollisionBitmask::INTERCEPTOR);
    return _sprite;
}

void Bullet::update(float dt)
{
    _velocity.y += BULLET_GRAVITY * dt;
    _position += Vec2(_velocity) * dt;
    _sprite->setPosition(_position);
}

bool Bullet::isVisible()
{
    if (_position.y < _landHeight) {
        return false;
    }

    const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
    if (_position.x > visibleSize.width + _sprite->getContentSize().width / 2.f) {
        return false;
    }

    return true;
}
