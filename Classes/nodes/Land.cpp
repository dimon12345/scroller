#include "Land.h"

USING_NS_CC;

cocos2d::Node* Land::create(const cocos2d::Size& visibleSize) {
	_visibleSize = visibleSize;
	_sprite = Sprite::create("world\\land.png");
	return _sprite;
}

void Land::setTilePosition(const Vec2 &position)
{
	_sprite->setPosition(position);
}
