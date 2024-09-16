#include "Background.h"

#include "GameSettings.h"

USING_NS_CC;

Node* Background::create()
{
    _backgroundNode = Node::create();

    for (int i = 0; i < BACKGROUND_CLOUDS_COUNT; ++i) {
        auto cloud = std::make_shared<Cloud>();
        auto cloudNode = cloud->create();
        _backgroundNode->addChild(cloudNode);
        _clouds.push_back(cloud);
    }

    return _backgroundNode;
}

void Background::restartClouds()
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
}
