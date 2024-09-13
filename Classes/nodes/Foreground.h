#pragma once

#include "cocos2d.h"

#include "nodes/Cloud.h"
#include "nodes/Land.h"

class Foreground {
	cocos2d::Node* _foregroundNode = nullptr;
	cocos2d::Size _visibleSize;
	std::list<std::shared_ptr<Land>> _landTiles;
	cocos2d::Vec2 _landVelocity;
	cocos2d::Vec2 _landPosition;
	cocos2d::Size _tileSize;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void update(float dt);
	float getTileHeight();
};
