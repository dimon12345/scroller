#include "GameEngine.h"

#include "nodes/EnemyFactory.h"
#include "nodes/Enemy.h"

USING_NS_CC;

//#define NEXT_ENEMY_DELAY 1.f
//#define NEXT_TIME_ADD_ENEMY 3.f

#define NEXT_ENEMY_DELAY 0.05f
#define NEXT_TIME_ADD_ENEMY 1.0f

GameEngine::GameEngine()
	: gameState(_gameState)
{
}

void GameEngine::createEnemy(Node* scene, const Size &visibleSize)
{
	std::shared_ptr<Enemy> enemy(EnemyFactory::createEnemy());

	auto sprite = enemy->create(visibleSize);
	scene->addChild(sprite);

	_gameState.enemies.push_back(enemy);
}

void GameEngine::killEnemy(Node* node)
{
	auto enemy = find_if(
		_gameState.enemies.begin(),
		_gameState.enemies.end(),
		[node](std::shared_ptr<Enemy> enemy) { return enemy->getNode() == node; }
	);

	if (enemy != _gameState.enemies.end()) {
		auto node = enemy->get()->getNode();
		node->getParent()->removeChild(node, true);
		_gameState.enemies.erase(enemy);
		_gameState.score += 100;
	}
}

void GameEngine::update(float dt, Node *scene, const Size &visibleSize)
{
	_gameState.nextTimeAddEnemy -= dt;
	if (_gameState.nextTimeAddEnemy <= 0) {
		_gameState.nextTimeAddEnemy = NEXT_TIME_ADD_ENEMY;
		++_gameState.maxEnemies;
	}

	_gameState.nextEnemyTime -= dt;
	if (_gameState.nextEnemyTime <= 0 && (_gameState.enemies.size() < _gameState.maxEnemies)) {
		_gameState.nextEnemyTime = NEXT_ENEMY_DELAY;
		createEnemy(scene, visibleSize);
	}

	for (auto enemyIt = _gameState.enemies.begin(); enemyIt != _gameState.enemies.end(); ++enemyIt) {
		(*enemyIt)->update(dt);
		if (!(*enemyIt)->isVisible()) {
			auto node = (*enemyIt)->getNode();
			node->getParent()->removeChild(node, true);
			_gameState.enemies.erase(enemyIt);
			_gameState.nextEnemyTime = NEXT_ENEMY_DELAY;
			createEnemy(scene, visibleSize);
			break;
		}
	}
}

void GameEngine::reset()
{
	_gameState.gameOver = false;
	_gameState.score = 0;

	_gameState.nextEnemyTime = NEXT_ENEMY_DELAY;
	_gameState.nextTimeAddEnemy = NEXT_TIME_ADD_ENEMY;
	_gameState.maxEnemies = 1;

	for (auto enemy : _gameState.enemies) {
		auto node = enemy->getNode();
		node->getParent()->removeChild(node);
	}
	_gameState.enemies.clear();
}

void GameEngine::gameOver()
{
	_gameState.gameOver = true;
}

void GameEngine::setLandHeight(float height)
{
	_gameState.landHeight = height;
}