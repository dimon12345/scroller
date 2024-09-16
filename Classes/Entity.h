#pragma once

#include "cocos2d.h"

class Entity
{
protected:
	cocos2d::Node* _sprite;

	void createCirclePhysicsBody(float scale, int categoryBitmask, int contactTestBitmask);

public:
	cocos2d::Node* getNode();
	virtual ~Entity();
};