#include "GameEngine.h"

#include "nodes/EnemyFactory.h"
#include "nodes/Enemy.h"
#include "nodes/EnemyBullet.h"
#include "nodes/Bullet.h"
#include "CollisionBitmask.h"
#include "GameSettings.h"

USING_NS_CC;

GameEngine::GameEngine()
	: gameState(_gameState)
{
}

GameEngine& GameEngine::getInstance()
{
	static GameEngine gameEngine;

	return gameEngine;
}

void GameEngine::setVisibleSize(const Size& visibleSize)
{
	_gameState.visibleSize = visibleSize;
}

void GameEngine::createEnemy(Node* scene)
{
	std::shared_ptr<Enemy> enemy(EnemyFactory::createEnemy());
	scene->addChild(enemy->create());
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

void GameEngine::update(float dt, Node *scene)
{
	_gameState.nextTimeAddEnemy -= dt;
	if (_gameState.nextTimeAddEnemy <= 0) {
		_gameState.nextTimeAddEnemy = NEXT_TIME_ADD_ENEMY;
		++_gameState.maxEnemies;
	}

	_gameState.nextEnemyTime -= dt;
	if (_gameState.nextEnemyTime <= 0 && (_gameState.enemies.size() < _gameState.maxEnemies)) {
		_gameState.nextEnemyTime = NEXT_ENEMY_DELAY;
		createEnemy(scene);
	}

	for (auto enemyIt = _gameState.enemies.begin(); enemyIt != _gameState.enemies.end(); ++enemyIt) {
		(*enemyIt)->update(dt);
		if (!(*enemyIt)->isVisible()) {
			auto node = (*enemyIt)->getNode();
			node->getParent()->removeChild(node, true);
			_gameState.enemies.erase(enemyIt);
			_gameState.nextEnemyTime = NEXT_ENEMY_DELAY;
			createEnemy(scene);
			break;
		}
	}

	updateEnemyBullets(dt);
	updateBullets(dt);
}

void GameEngine::updateBullets(float dt)
{
	for (auto const& bullet : _gameState.bullets) {
		bullet->update(dt);
	}

	std::list<std::shared_ptr<Bullet>> result;
	bool updated = false;
	std::copy_if(
		_gameState.bullets.begin(),
		_gameState.bullets.end(),
		std::back_inserter(result),
		[updated, this](std::shared_ptr<Bullet>& bullet) {
			if (!bullet->isVisible()) {
				auto node = bullet->getNode();
				node->getParent()->removeChild(node, true);
				return false;
			}
			else return true;
		}
	);

	if (result.size() != _gameState.bullets.size()) {
		_gameState.bullets = result;
	}
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

	for (auto bullet : _gameState.bullets) {
		auto node = bullet->getNode();
		node->getParent()->removeChild(bullet->getNode());
	}
	_gameState.bullets.clear();
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

void GameEngine::fire(cocos2d::Node *scene, cocos2d::Vec2& position) {
	auto bullet = std::make_shared<Bullet>();
	_gameState.bullets.push_back(bullet);
	auto bulletSprite = bullet->create(position, GameEngine::getInstance().gameState.landHeight);
	scene->addChild(bulletSprite);
}