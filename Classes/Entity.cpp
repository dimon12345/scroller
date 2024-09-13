#include "Entity.h"

USING_NS_CC;

Entity::~Entity() {
}

cocos2d::Node* Entity::getNode() {
	return _sprite;
}

void Entity::createCirclePhysicsBody(float scale, int categoryBitmask, int contactTestBitmask) {
	auto body = PhysicsBody::createCircle(_sprite->getContentSize().width * scale);
	_sprite->setPhysicsBody(body);
	body->setCategoryBitmask(categoryBitmask);
	body->setContactTestBitmask(contactTestBitmask);
	body->setDynamic(false);
}