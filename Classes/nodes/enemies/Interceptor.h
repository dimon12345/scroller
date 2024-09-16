#pragma once

#include "nodes/Enemy.h"

#include "cocos2d.h"

class GameEngine;
class EnemyBullet;

class Interceptor : public Enemy
{
	void updateVerticalVelocity(float dt);
protected:
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;
	float _nextShotTime;
	float _minHeight;
	void fire();

public:
	~Interceptor();
	virtual cocos2d::Node* create();
	virtual void update(float dt);
	virtual bool isVisible();
	virtual void reset();
};
