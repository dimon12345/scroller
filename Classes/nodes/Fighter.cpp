#include "Fighter.h"

#include "Bullet.h"
#include "CollisionBitmask.h"

#include <iostream>
#include <algorithm>

USING_NS_CC;

#define FIGHTER_ACCELERATION_RATE 200.f
#define FIGHTER_MAX_VELOCITY 300.f
#define FIGHTER_STOP_DISTANCE 10.f
#define FIGHTER_BREAK_ACCELERATION_RATE -400.f
#define FIGHTER_ON_PLACE_EPSILON 2.f
#define FIGHTER_NEXT_SHOT_TIME_INTERVAL 0.3f

#define LAND_HEIGHT 0.1f

Node* Fighter::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _positionY = _visibleSize.height / 2;

    _sprite = Sprite::create("world\\fighter.png");
    _sprite->setTag(33);
    createCirclePhysicsBody(
        0.2f,
        CollisionBitmask::FIGHTER,
        CollisionBitmask::BOMBER |
            CollisionBitmask::INTERCEPTOR |
            CollisionBitmask::METEOR |
            CollisionBitmask::BIRD |
            CollisionBitmask::ENEMY_BULLET
    );

    _xOffset = visibleSize.width * 0.3f;
    _sprite->setPosition(Vec2(_xOffset, _positionY));
    _fighterHeight = _sprite->getContentSize().height;

    reset();

    return _sprite;
}

void Fighter::reset() {
    _fire = false;
    for (auto bullet: _bullets) {
        _sprite->getParent()->removeChild(bullet->getNode());
    }
    _bullets.clear();
}

void Fighter::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    _cursorY = e->getCursorY();
}

void Fighter::onMouseDown(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        _fire = true;
    }
}

void Fighter::onMouseUp(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        _fire = false;
    }
}

void Fighter::update(float dt)
{
    updatePosition(dt);
    updateBullets(dt);
}

void Fighter::updatePosition(float dt) {
    auto distance = abs(_cursorY - _positionY);
    auto distanceEpsilon = FIGHTER_MAX_VELOCITY * dt;

    if (distance > distanceEpsilon) {
        if (_cursorY - _positionY > 0) {
            _positionY += FIGHTER_MAX_VELOCITY * dt;
        }
        else {
            _positionY -= FIGHTER_MAX_VELOCITY * dt;
        }
    }
    else {
        _positionY = _cursorY;
    }

    _positionY = clampf(_positionY, 0, _visibleSize.height);
    _sprite->setPosition(Vec2(_xOffset, _positionY));

    if (_positionY - _fighterHeight / 2 < GameEngine::getInstance().gameState.landHeight) {
        GameEngine::getInstance().gameOver();
        return;
    }
}

void Fighter::updateBullets(float dt) {
    for (auto const& bullet : _bullets) {
        bullet->update(dt);
    }

    std::list<std::shared_ptr<Bullet>> result;
    bool updated = false;
    std::copy_if(
        _bullets.begin(),
        _bullets.end(),
        std::back_inserter(result),
        [updated, this](std::shared_ptr<Bullet>& bullet) {
            if (!bullet->isVisible()) {
                auto node = bullet->getNode();
                node->getParent()->removeChild(node, true);
                return false;
            }
            else return true;
        }
    );

    if (result.size() != _bullets.size()) {
        _bullets = result;
    }

    _nextShotTime -= dt;

    if (!_fire) {
        return;
    }

    if (_nextShotTime < 0) {
        _nextShotTime = FIGHTER_NEXT_SHOT_TIME_INTERVAL;
        auto bullet = std::make_shared<Bullet>();
        _bullets.push_back(bullet);
        auto bulletSprite = bullet->create(_visibleSize, Vec2(_xOffset, _positionY), GameEngine::getInstance().gameState.landHeight);
        _sprite->getParent()->addChild(bulletSprite);
    }
}
