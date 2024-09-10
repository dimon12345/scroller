#pragma once

#include "nodes/Enemy.h"

#include "cocos2d.h"

class Bird : public Enemy
{
	cocos2d::Size _visibleSize;
	cocos2d::Sprite* _birdSprite;
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

	float _changeDirectionTime;

public:
	virtual cocos2d::Node* create(const cocos2d::Size& visibleSize);
	virtual void update(float dt);
	virtual bool isVisible();
	virtual void reset();
};
