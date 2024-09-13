#pragma once

#include "nodes/Enemy.h"

#include "cocos2d.h"

class Interceptor : public Enemy
{
protected:
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

public:
	virtual cocos2d::Node* create(const cocos2d::Size& visibleSize);
	virtual void update(float dt);
	virtual bool isVisible();
	virtual void reset();
};
