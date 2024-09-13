#pragma once

#include "GameState.h"

#include <cocos2d.h>

class GameEngine {
	GameState _gameState;

	void updateEnemyBullets(float dt);
	GameEngine();
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator= (const GameEngine &engine) = delete;

public:
	static GameEngine& getInstance();
	
	const GameState &gameState;

	void createEnemy(cocos2d::Node* scene, const cocos2d::Size& visibleSize);
	void killEnemy(cocos2d::Node *node);

	void update(float dt, cocos2d::Node *scene, const cocos2d::Size& visibleSize);
	void reset();

	void gameOver();

	void setLandHeight(float height);

	void addEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
};
