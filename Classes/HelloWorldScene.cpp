/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

#include "nodes/EnemyFactory.h"

USING_NS_CC;

#define METEOR_MAX_TIME 15.f
#define METEOR_MIN_TIME 10.f

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    GameEngine::getInstance().setVisibleSize(visibleSize);

    auto bg = LayerColor::create(Color4B(136, 210, 242, 255));
    this->addChild(bg, -2);

    scheduleUpdate();

    // button
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = origin.y + closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

    // background
    auto backgroundNode = _background.create();
    this->addChild(backgroundNode, -1);

    // foreground
    auto foregroundNode = _foreground.create();
    this->addChild(foregroundNode, 1);

    GameEngine::getInstance().setLandHeight(_foreground.getTileHeight());
    

    this->addChild(_fighter.create());

    // score

    auto scoreLabel = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 30);
    scoreLabel->setColor(Color3B(54, 105, 13));
    _scoreY = visibleSize.height - 30 - scoreLabel->getContentSize().height;
    _scoreXOffset = 30 + scoreLabel->getContentSize().width / 2;
    scoreLabel->setPosition(
        Vec2(
            _scoreXOffset,
            _scoreY
        )
    );
    this->addChild(scoreLabel);
    _scoreXOffset += scoreLabel->getContentSize().width / 2 + 30;

    _score = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
    _oldScore = 0;
    _score->setColor(Color3B(34, 85, 7));
    _score->setPosition(
        Vec2(
            _scoreXOffset + _score->getContentSize().width /2,
            _scoreY
        )
    );
    this->addChild(_score);

    // player events
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameEngine::onContactBegin, &GameEngine::getInstance());
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Fighter::onMouseDown, &_fighter);
    _mouseListener->onMouseUp = CC_CALLBACK_1(Fighter::onMouseUp, &_fighter);
    _mouseListener->onMouseMove = CC_CALLBACK_1(Fighter::onMouseMove, &_fighter);

    _eventDispatcher->addEventListenerWithFixedPriority(_mouseListener, 1);

    this->addChild(_meteor.create(GameEngine::getInstance().gameState.landHeight));
    _nextTimeShowMeteor = random(METEOR_MIN_TIME, METEOR_MAX_TIME);

    reset();

    return true;
}

void HelloWorld::update(float dt)
{
    const Size& visibleSize = GameEngine::getInstance().gameState.visibleSize;
    if (GameEngine::getInstance().gameState.gameOver) {
        if (!_gameOverLabel) {
            _gameOverLabel = Label::createWithTTF("Game\nover!", "fonts/Marker Felt.ttf", 124);
            _gameOverLabel->setTextColor(Color4B(120, 12, 12, 255));
            _gameOverLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(_gameOverLabel, 1);
        }

        if (!_restartButton) {
            auto restartLabel = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 124);
            float padding = 30.0f;
            float yPosition = visibleSize.height / 2.f - padding - restartLabel->getContentSize().width / 2.f;
            auto buttonPosition = Vec2(visibleSize.width / 2, yPosition);

            _drawNode = DrawNode::create();
            _drawNode->drawSolidRect(
                buttonPosition - restartLabel->getContentSize()/2.f - Vec2(padding, padding),
                buttonPosition + restartLabel->getContentSize()/2.f + Vec2(padding, padding),
                Color4F(0.5f, 0.7f, 0.4f, 1.f)
            );
            this->addChild(_drawNode);
            
            restartLabel->setColor(Color3B(54, 105, 13));
            auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(HelloWorld::restartGameButtonPressed, this));
            restartItem->setPosition(buttonPosition);

            _restartButton = Menu::create(restartItem, NULL);
            _restartButton->setPosition(Vec2::ZERO);
            this->addChild(_restartButton, 1);
        }

        return;
    }

    _background.update(dt);
    _foreground.update(dt);
    _fighter.update(dt);

    GameEngine::getInstance().update(dt, this);

    if (_oldScore != GameEngine::getInstance().gameState.score) {
        _oldScore = GameEngine::getInstance().gameState.score;
        char buf[30];
        _itoa(_oldScore, buf, 10);
        _score->setString(buf);

        _score->setPosition(
            Vec2(
                _scoreXOffset + _score->getContentSize().width / 2,
                _scoreY
            )
        );
    }

    _nextTimeShowMeteor -= dt;
    if (_nextTimeShowMeteor < 0) {
        _nextTimeShowMeteor = random(METEOR_MIN_TIME, METEOR_MAX_TIME);

        _meteor.restart();
    }

    _meteor.update(dt);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
        Director::getInstance()->end();
}

void HelloWorld::restartGameButtonPressed(Ref* pSender)
{
    reset();
}

void HelloWorld::reset()
{
    GameEngine::getInstance().reset();

    _fighter.reset();

    if (_gameOverLabel) {
        this->removeChild(_gameOverLabel);
        _gameOverLabel = nullptr;
    }

    if (_restartButton) {
        this->removeChild(_restartButton);
        _restartButton = nullptr;
    }

    if (_drawNode) {
        this->removeChild(_drawNode);
        _drawNode = nullptr;
    }

    _meteor.hide();

    _background.restartClouds(true);
}