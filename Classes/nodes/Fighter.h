#pragma once

#include "Bullet.h"

#include "cocos2d.h"

#include <list>
#include <memory>

#include "Entity.h"
#include "GameEngine.h"

class Fighter : public Entity {
	float _cursorY;
	float _positionY;
	float _xOffset;
	bool _fire = false;
	float _nextShotTime;
	float _fighterHeight;
	float _maxHeight;

	void updatePosition(float ft);
	void updateNextShot(float ft);

public:
	cocos2d::Node* create();
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void update(float dt);
	void reset();
};
