#pragma once

#include "Entity.h"

#include "cocos2d.h"

class EnemyBullet : public Entity {
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

public:
	cocos2d::Node* create(const cocos2d::Vec2& position);
	void update(float dt);
	bool isVisible();
};
