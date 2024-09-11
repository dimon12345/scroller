#pragma once

#include "cocos2d.h"

#include "Entity.h"

class Enemy : public Entity {
public:
	virtual cocos2d::Node* create(const cocos2d::Size& visibleSize) = 0;
	virtual void update(float dt) = 0;
	virtual bool isVisible() = 0;
	virtual void reset() = 0;
};