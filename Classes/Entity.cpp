#include "Entity.h"

Entity::~Entity() {
}

cocos2d::Node* Entity::getNode() {
	return _sprite;
}
