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
#define ENEMY_NODE_TAG 44

Node* Fighter::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _positionY = _visibleSize.height / 2;

    _sprite = Sprite::create("world\\fighter.png");
    _sprite->setTag(FIGHTER_NODE_TAG);
    createCirclePhysicsBody(0.2f, 0x0f, 0x2);

    _xOffset = visibleSize.width * 0.3f;
    _sprite->setPosition(Vec2(_xOffset, _positionY));

    reset();

    return _sprite;
}

void Fighter::setGameEngine(std::shared_ptr<GameEngine> gameEngine)
{
    _gameEngine = gameEngine;
}


void Fighter::reset() {
    _fire = false;
    for (auto bullet: _bullets) {
        _sprite->getParent()->removeChild(bullet->getNode());
    }
    _bullets.clear();
}

bool Fighter::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    if (nodeA == nullptr) {
        return false;
    }

    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeB == nullptr) {
        return false;
    }

    auto tagA = nodeA->getTag();
    auto tagB = nodeB->getTag();
    if (tagA == tagB) {
        return false;
    }

    auto bitmaskA = contact.getShapeA()->getCategoryBitmask();
    auto bitmaskB = contact.getShapeB()->getCategoryBitmask();

    if (contact.getShapeA()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
        _gameEngine->gameOver();
        return true;
    }

    if (contact.getShapeB()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
        _gameEngine->gameOver();
        return true;
    }

    if (contact.getShapeA()->getBody()->getNode()->getTag() == 44) {
        destroyEnemy(contact.getShapeA()->getBody()->getNode());
        return true;
    }

    if (contact.getShapeB()->getBody()->getNode()->getTag() == 44) {
        destroyEnemy(contact.getShapeA()->getBody()->getNode());
        return true;
    }

    return false;
}

void Fighter::destroyEnemy(Node *enemy)
{
    _gameEngine->destroyEnemy(enemy);
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

    _sprite->setPosition(Vec2(_xOffset, _positionY));
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
                _sprite->removeChild(bullet->getNode(), true);
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
        _sprite->getParent()->addChild(bulletSprite);
    }
}
