#pragma once

#include "cocos2d.h"

class Entity
{
protected:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;
	cocos2d::Node* _sprite;
public:
	cocos2d::Node* getNode();
	virtual ~Entity();
};