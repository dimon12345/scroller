#pragma once

#include "Entity.h"

#include "cocos2d.h"

class Cloud : public Entity
{
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void restartPosition(bool randomX);
	void update(float dt);
};
