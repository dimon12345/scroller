#pragma once

#include "nodes/Enemy.h"

class Bomber : public Enemy {
protected:
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

public:
	virtual cocos2d::Node* create();
	virtual void update(float dt);
	virtual bool isVisible();
};
