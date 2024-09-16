#pragma once

#include "GameState.h"

#include <cocos2d.h>

class GameEngine {
	GameState _gameState;

	void updateEnemyBullets(float dt);
	void updateBullets(float dt);
	GameEngine();
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator= (const GameEngine &engine) = delete;

public:
	static GameEngine& getInstance();
	
	const GameState &gameState;

	void createEnemy(cocos2d::Node* scene);
	void killEnemy(cocos2d::Node *node);

	void update(float dt, cocos2d::Node *scene);
	void reset();

	void gameOver();

	void setLandHeight(float height);

	void addEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	void fire(cocos2d::Node* scene, cocos2d::Vec2& position);

	void setVisibleSize(const cocos2d::Size& visibleSize);
};
