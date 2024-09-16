#include "Foreground.h"

#include "GameEngine.h"

USING_NS_CC;

#define LAND_VELOCITY 500

Node* Foreground::create()
{
    _foregroundNode = Node::create();

    auto tmpSprite = Sprite::create("world\\land.png");
    _tileSize = tmpSprite->getContentSize();

    const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
    float fullSize = 0;
    while (fullSize < visibleSize.width + _tileSize.width/2) {
        auto tile = std::make_shared<Land>();
        auto tileNode = tile->create();
        float width = tileNode->getContentSize().width;
        float height = tileNode->getContentSize().height;
        fullSize += width;
        _foregroundNode->addChild(tileNode);
        _landTiles.push_back(tile);
    }

    _landVelocity = Vec2(-LAND_VELOCITY, 0);
    _landPosition = Vec2(0, _tileSize.height/2);

    return _foregroundNode;
}

void Foreground::update(float dt)
{
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

float Foreground::getTileHeight()
{
    return _tileSize.height;
}
