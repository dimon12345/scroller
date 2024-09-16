#pragma once

#include "Entity.h"

class Land : public Entity
{
	cocos2d::Vec2 _velocity;
public:
	cocos2d::Node* create();
	void setTilePosition(const cocos2d::Vec2& position);
};