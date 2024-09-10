#pragma once

#include "cocos2d.h"

class Background {
	cocos2d::Sprite* _cloudSprite;
	cocos2d::Size _visibleSize;
	void restartClouds(bool randomX);
	cocos2d::Vec2 _points[2];
public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void stop();
};
