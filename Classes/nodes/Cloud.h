#pragma once

#include "Entity.h"

#include "cocos2d.h"

class Cloud : public Entity
{
public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void restartPosition(bool randomX);
	void update(float dt);
};
