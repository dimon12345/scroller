#pragma once

#include "cocos2d.h"

class Fighter {
	cocos2d::Sprite* _fighterSprite;
	cocos2d::Size _visibleSize;
	float _cursorY;
	float _positionY;
	float _xOffset;
	bool _fire;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void update(float dt);
};
