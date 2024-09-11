#include "Fighter.h"

#include "Bullet.h"

#include <iostream>
#include <algorithm>

USING_NS_CC;

#define FIGHTER_ACCELERATION_RATE 200.f
#define FIGHTER_MAX_VELOCITY 300.f
#define FIGHTER_STOP_DISTANCE 10.f
#define FIGHTER_BREAK_ACCELERATION_RATE -400.f
#define FIGHTER_ON_PLACE_EPSILON 2.f
#define FIGHTER_NEXT_SHOT_TIME_INTERVAL 0.2f
#define FIGHTER_NODE_TAG 33

Fighter::Fighter(bool& gameOver)
    : _gameOver(gameOver)
{

}

Node* Fighter::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _positionY = _visibleSize.height / 2;

    _fighterSprite = Sprite::create("world\\fighter.png");
    _fighterSprite->setTag(FIGHTER_NODE_TAG);
    auto body = PhysicsBody::createBox(_fighterSprite->getContentSize());
    _fighterSprite->setPhysicsBody(body);
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);

    _xOffset = visibleSize.width * 0.3f;
    _fighterSprite->setPosition(Vec2(_xOffset, _positionY));

    reset();

    return _fighterSprite;
}

void Fighter::reset() {
    _fire = false;
    for (auto bullet: _bullets) {
        _fighterSprite->getParent()->removeChild(bullet->getSprite());
    }
    _bullets.clear();
}

bool Fighter::onContactBegin(PhysicsContact& contact)
{
    //auto shapeA = contact.getShapeA();
    //auto shapeB = contact.getShapeB();
    //if ((shapeA->getCategoryBitmask() & shapeB->getCollisionBitmask()) == 0
    //    || (shapeB->getCategoryBitmask() & shapeA->getCollisionBitmask()) == 0)
    //{
    //    return false;
    //}

    if (contact.getShapeA()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
        _gameOver = true;
        return true;
    }

    if (contact.getShapeB()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
        _gameOver = true;
        return true;
    }

    return false;

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
