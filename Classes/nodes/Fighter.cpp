#include "Fighter.h"

#include "Bullet.h"

#include <iostream>
#include <algorithm>

USING_NS_CC;

#define FIGHTER_ACCELERATION_RATE 200.f
#define FIGHTER_MAX_VELOCITY 200.f
#define FIGHTER_STOP_DISTANCE 10.f
#define FIGHTER_BREAK_ACCELERATION_RATE -400.f
#define FIGHTER_ON_PLACE_EPSILON 2.f
#define FIGHTER_NEXT_SHOT_TIME_INTERVAL 0.2f

Node* Fighter::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _positionY = _visibleSize.height / 2;

    _fighterSprite = Sprite::create("world\\fighter.png");
    _xOffset = visibleSize.width * 0.3f;
    _fighterSprite->setPosition(Vec2(_xOffset, _positionY));

    return _fighterSprite;
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
        _nextShotTime = 0;
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
    float maxVelocity = 200;
    auto distance = abs(_cursorY - _positionY);
    auto distanceEpsilon = maxVelocity * dt;

    if (distance > distanceEpsilon) {
        if (_cursorY - _positionY > 0) {
            _positionY += maxVelocity * dt;
        }
        else {
            _positionY -= maxVelocity * dt;
        }
    }
    else {
        _positionY = _cursorY;
    }

    _fighterSprite->setPosition(Vec2(_xOffset, _positionY));
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
                _fighterSprite->removeChild(bullet->getSprite(), true);
                return false;
            }
            else return true;
        }
    );

    if (result.size() != _bullets.size()) {
        _bullets = result;
    }

    if (!_fire) {
        return;
    }

    _nextShotTime -= dt;

    if (_nextShotTime < 0) {
        _nextShotTime = FIGHTER_NEXT_SHOT_TIME_INTERVAL;
        auto bullet = std::make_shared<Bullet>();
        _bullets.push_back(bullet);
        auto bulletSprite = bullet->create(_visibleSize, Vec2(_xOffset, _positionY));
        _fighterSprite->getParent()->addChild(bulletSprite);
    }
}

