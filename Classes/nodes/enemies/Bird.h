#pragma once

#include "nodes/Enemy.h"

#include "cocos2d.h"

class Bird : public Enemy
{
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

	float _changeDirectionTime;
	float _minHeight;
	float _maxHeight;

public:
	virtual cocos2d::Node* create();
	virtual void update(float dt);
	virtual bool isVisible();
	virtual void reset();
};
