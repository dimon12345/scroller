#pragma once

#include "cocos2d.h"

class Bullet {
	cocos2d::Size _visibleSize;
	cocos2d::Sprite* _bulletSprite;
	cocos2d::Vec2 _position;
	cocos2d::Vec2 _velocity;

public:

	Bullet();
	~Bullet();

	cocos2d::Node* create(const cocos2d::Size& visibleSize, const cocos2d::Vec2& position);
	void update(float dt);
	bool isVisible();
	cocos2d::Sprite* getSprite();
};
