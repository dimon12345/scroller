#pragma once

#include "GameState.h"

#include <cocos2d.h>

class GameEngine {
	GameState _gameState;

public:
	GameEngine();
	const GameState &gameState;

	void createEnemy(cocos2d::Node* scene, const cocos2d::Size& visibleSize);
	void killEnemy(cocos2d::Node *node);

	void update(float dt, cocos2d::Node *scene, const cocos2d::Size& visibleSize);
	void reset();

	void gameOver();

	void setLandHeight(float height);
};
