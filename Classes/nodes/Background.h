#pragma once

#include "cocos2d.h"

#include "nodes/Cloud.h"
#include "nodes/Land.h"

class Background {
	cocos2d::Node* _backgroundNode = nullptr;
	cocos2d::Node* _cloudSprite = nullptr;
	cocos2d::Size _visibleSize;
	std::list<std::shared_ptr<Cloud>> _clouds;
	std::list<std::shared_ptr<Land>> _landTiles;
	cocos2d::Vec2 _landVelocity;
	cocos2d::Vec2 _landPosition;
	cocos2d::Size _tileSize;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void restartClouds(bool randomX);
	void update(float dt);
	float getTileHeight();
};
