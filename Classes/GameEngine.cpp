#include "GameEngine.h"

#include "nodes/EnemyFactory.h"
#include "nodes/Enemy.h"
#include "nodes/EnemyBullet.h"

USING_NS_CC;

//#define NEXT_ENEMY_DELAY 1.f
//#define NEXT_TIME_ADD_ENEMY 3.f

#define NEXT_ENEMY_DELAY 0.05f
#define NEXT_TIME_ADD_ENEMY 1.0f

#define FIGHTER_NODE_TAG 33
//#define ENEMY_NODE_TAG 44
//

GameEngine::GameEngine()
	: gameState(_gameState)
{
}

GameEngine& GameEngine::getInstance()
{
	static GameEngine gameEngine;

	return gameEngine;

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

	updateEnemyBullets(dt);
}

void GameEngine::updateEnemyBullets(float dt)
{
	for (auto enemyBullet : _gameState.enemyBullets) {
		enemyBullet->update(dt);
	}

	std::list<std::shared_ptr<EnemyBullet>> result;
	bool updated = false;
	std::copy_if(
		_gameState.enemyBullets.begin(),
		_gameState.enemyBullets.end(),
		std::back_inserter(result),
		[updated, this](std::shared_ptr<EnemyBullet>& bullet) {
			if (!bullet->isVisible()) {
				auto node = bullet->getNode();
				node->getParent()->removeChild(node, true);
				return false;
			}
			else return true;
		}
	);

	if (result.size() != _gameState.enemyBullets.size()) {
		_gameState.enemyBullets = result;
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

	for (auto enemyBullet : _gameState.enemyBullets) {
		auto node = enemyBullet->getNode();
		node->getParent()->removeChild(node);
	}
	_gameState.enemyBullets.clear();
}

void GameEngine::gameOver()
{
	_gameState.gameOver = true;
}

void GameEngine::setLandHeight(float height)
{
	_gameState.landHeight = height;
}

void GameEngine::addEnemyBullet(std::shared_ptr<EnemyBullet> enemyBullet)
{
	_gameState.enemyBullets.push_back(enemyBullet);
}

bool GameEngine::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	if (nodeA == nullptr) {
		return false;
	}

	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeB == nullptr) {
		return false;
	}

	auto tagA = nodeA->getTag();
	auto tagB = nodeB->getTag();
	if (tagA == tagB) {
		return false;
	}

	auto bitmaskA = contact.getShapeA()->getCategoryBitmask();
	auto bitmaskB = contact.getShapeB()->getCategoryBitmask();

	if (contact.getShapeA()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
		GameEngine::getInstance().gameOver();
		return true;
	}

	if (contact.getShapeB()->getBody()->getNode()->getTag() == FIGHTER_NODE_TAG) {
		GameEngine::getInstance().gameOver();
		return true;
	}

	if (contact.getShapeA()->getBody()->getNode()->getTag() == 44) {
		auto body = contact.getShapeA()->getBody();
		GameEngine::getInstance().killEnemy(body->getNode());
		return true;
	}

	if (contact.getShapeB()->getBody()->getNode()->getTag() == 44) {
		auto body = contact.getShapeB()->getBody();
		GameEngine::getInstance().killEnemy(body->getNode());
		return true;
	}

	return false;
}
