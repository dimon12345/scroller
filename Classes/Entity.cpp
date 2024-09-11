#include "Entity.h"

USING_NS_CC;

Entity::~Entity() {
}

cocos2d::Node* Entity::getNode() {
	return _sprite;
}

void Entity::createCirclePhysicsBody(float scale, int contactTestBitmask, int categoryBitmask) {
	auto body = PhysicsBody::createCircle(_sprite->getContentSize().width * scale);
	_sprite->setPhysicsBody(body);
	body->setContactTestBitmask(contactTestBitmask);
	body->setCategoryBitmask(categoryBitmask);
	body->setDynamic(false);
}