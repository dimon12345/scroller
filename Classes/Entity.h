#pragma once

#include "cocos2d.h"

class Entity
{
protected:
	cocos2d::Size _visibleSize;
	cocos2d::Node* _sprite;

	void createCirclePhysicsBody(float scale, int contactTestBitmask, int categoryBitmask);

public:
	cocos2d::Node* getNode();
	virtual ~Entity();
};