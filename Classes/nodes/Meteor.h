#pragma once

#include "Entity.h"

#include "cocos2d.h"

class Meteor : public Entity
{
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;
	bool _visible;
	bool checkVisibility();
	cocos2d::Size _size;
	float _landHeight;
public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize, float landHeight);
	void restart();
	void update(float dt);
};