#pragma once

#include "Bullet.h"

#include "cocos2d.h"

#include <list>
#include <memory>

#include "Entity.h"
#include "GameEngine.h"

class Fighter : public Entity {
	cocos2d::Size _visibleSize;
	float _cursorY;
	float _positionY;
	float _xOffset;
	bool _fire = false;
	float _nextShotTime;
	float _fighterHeight;

	void updatePosition(float ft);
	void updateBullets(float ft);

	std::list<std::shared_ptr<Bullet>> _bullets;

	std::shared_ptr<GameEngine> _gameEngine;

public:
	cocos2d::Node* create(const cocos2d::Size& visibleSize);
	void setGameEngine(std::shared_ptr<GameEngine> gameEngine);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void update(float dt);
	void reset();
};
