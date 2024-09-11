#pragma once

#include "Bullet.h"

#include "cocos2d.h"

#include <list>
#include <memory>

class Fighter {
	cocos2d::Sprite* _fighterSprite;
	cocos2d::Size _visibleSize;
	float _cursorY;
	float _positionY;
	float _xOffset;
	bool _fire = false;
	float _nextShotTime;

	void updatePosition(float ft);
	void updateBullets(float ft);

	std::list<std::shared_ptr<Bullet>> _bullets;

	bool& _gameOver;

public:
	Fighter(bool& gameOver);
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void update(float dt);
	void reset();
};
