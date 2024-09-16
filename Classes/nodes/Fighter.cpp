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

Node* Fighter::create()
{
    const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
    _positionY = visibleSize.height / 2;

    _sprite = Sprite::create("world\\fighter.png");
    _sprite->setTag(FIGHTER_NODE_TAG);
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
    _maxHeight = GameEngine::getInstance().gameState.visibleSize.height;

    reset();

    return _sprite;
}

void Fighter::reset() {
    _fire = false;
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

    _positionY = clampf(_positionY, 0, _maxHeight);
    _sprite->setPosition(Vec2(_xOffset, _positionY));

    if (_positionY - _fighterHeight / 2 < GameEngine::getInstance().gameState.landHeight) {
        GameEngine::getInstance().gameOver();
        return;
    }
}

void Fighter::updateBullets(float dt) {
    
    _nextShotTime -= dt;

    if (!_fire) {
        return;
    }

    if (_nextShotTime < 0) {
        _nextShotTime = FIGHTER_NEXT_SHOT_TIME_INTERVAL;

        GameEngine::getInstance().fire(_sprite->getParent(), Vec2(_xOffset, _positionY));
    }
}
