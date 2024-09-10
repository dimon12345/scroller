#include "Background.h"

USING_NS_CC;

#define CLOUDS_ANIMATION_DURATION 30.0f

Node* Background::create(const cocos2d::Size& visibleSize)
{
    _visibleSize = visibleSize;
    _cloudSprite = Sprite::create("world\\cloud.png");
    float spriteWidth = _cloudSprite->getContentSize().width;
    _points[0] = Vec2(_visibleSize.width + spriteWidth/2.f, 0);
    _points[1] = Vec2(-spriteWidth/2.f, 0.f);

    restartClouds(true);
    return _cloudSprite;
}

void Background::restartClouds(bool randomX = false)
{
    _cloudSprite->stopAllActions();

    float x = 0.f;
    float timeRemained = CLOUDS_ANIMATION_DURATION;

    if (randomX) {
        float rnd = random(0.f, 1.f);
        float spriteWidth = _cloudSprite->getContentSize().width;
        x = -spriteWidth/2 + rnd * (_visibleSize.width + spriteWidth);
        
        timeRemained = CLOUDS_ANIMATION_DURATION * (1 - rnd);
    }

    float randomHeight = random(0.f, _visibleSize.height);
    auto randomOffsetBegin = Vec2(-x, randomHeight);
    auto randomOffsetEnd = Vec2(0, randomHeight);

    auto moveToAction1 = MoveTo::create(0.f, _points[0] + randomOffsetBegin);
    auto moveToAction2 = MoveTo::create(timeRemained, _points[1] + randomOffsetEnd);
    auto cloudSequence = Sequence::create(moveToAction1, moveToAction2, CallFunc::create([this] { restartClouds(); }), nullptr);

    _cloudSprite->setPosition(Vec2::ZERO);
    _cloudSprite->runAction(cloudSequence);
}

void Background::stop()
{
    _cloudSprite->stopAllActions();
}