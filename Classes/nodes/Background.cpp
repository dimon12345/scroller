#include "Background.h"

USING_NS_CC;

#define BACKGROUND_CLOUDS_COUNT 50
#define LAND_VELOCITY 500

Node* Background::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _backgroundNode = Node::create();

    for (int i = 0; i < BACKGROUND_CLOUDS_COUNT; ++i) {
        auto cloud = std::make_shared<Cloud>();
        auto cloudNode = cloud->create(_visibleSize);
        _backgroundNode->addChild(cloudNode);
        _clouds.push_back(cloud);
    }

    auto tmpSprite = Sprite::create("world\\land.png");
    _tileSize = tmpSprite->getContentSize();

    float fullSize = 0;
    while (fullSize < _visibleSize.width + _tileSize.width/2) {
        auto tile = std::make_shared<Land>();
        auto tileNode = tile->create(visibleSize);
        float width = tileNode->getContentSize().width;
        float height = tileNode->getContentSize().height;
        fullSize += width;
        _backgroundNode->addChild(tileNode);
        _landTiles.push_back(tile);
    }

    _landVelocity = Vec2(-LAND_VELOCITY, 0);
    _landPosition = Vec2(0, _tileSize.height/2);

    return _backgroundNode;
}

void Background::restartClouds(bool randomX = false)
{
    for (auto cloud : _clouds) {
        cloud->restartPosition(true);
    }
}

void Background::update(float dt)
{
    for (auto cloud : _clouds) {
        cloud->update(dt);
    }

    _landPosition += _landVelocity * dt;
    if(_landPosition.x < -_tileSize.width / 2) {
        _landPosition += Vec2(_tileSize.width, 0);
    }

    auto nextPosition = _landPosition;
    for (auto tile : _landTiles) {
        tile->setTilePosition(nextPosition);
        nextPosition += Vec2(_tileSize.width, 0);
    }
}
