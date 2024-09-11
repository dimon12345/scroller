#pragma once

#include "cocos2d.h"

#include "nodes/Cloud.h"

class Background {
	cocos2d::Node* _backgroundNode = nullptr;
	cocos2d::Node* _cloudSprite = nullptr;
	cocos2d::Size _visibleSize;
	std::list<std::shared_ptr<Cloud>> _clouds;
public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void restartClouds(bool randomX);
	void update(float dt);
};
