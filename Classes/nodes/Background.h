#pragma once

#include "cocos2d.h"

#include "nodes/Cloud.h"
#include "nodes/Land.h"

class Background {
	cocos2d::Node* _backgroundNode = nullptr;
	cocos2d::Node* _cloudSprite = nullptr;
	std::list<std::shared_ptr<Cloud>> _clouds;
public:
	cocos2d::Node* create();
	void restartClouds(bool randomX);
	void update(float dt);
};
