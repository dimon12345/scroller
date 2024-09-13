#pragma once

#include "Entity.h"

#include "cocos2d.h"

class Bullet : public Entity {
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;
	float _landHeight;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize, const cocos2d::Vec2& position, float landHeight);
	void update(float dt);
	bool isVisible();
};
