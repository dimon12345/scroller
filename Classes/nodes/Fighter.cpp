#include "Fighter.h"

#include <iostream>

USING_NS_CC;

#define FIGHTER_ACCELERATION_RATE 200.f
#define FIGHTER_MAX_VELOCITY 200.f
#define FIGHTER_STOP_DISTANCE 10.f
#define FIGHTER_BREAK_ACCELERATION_RATE -400.f
#define FIGHTER_ON_PLACE_EPSILON 2.f

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
