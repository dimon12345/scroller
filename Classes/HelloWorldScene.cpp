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

//#include <utility>

USING_NS_CC;

#define NEXT_ENEMY_DELAY 1.0f
#define NEXT_TIME_ADD_ENEMY 3.0f

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = LayerColor::create(Color4B(136, 210, 242, 255));
    this->addChild(bg, -2);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + _visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + _visibleSize.width/2,
                                origin.y + _visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    for (int i = 0; i < CLOUNDS_COUNT; ++i) {
        auto cloudSprite = _backgrounds[i].create(_visibleSize);
        this->addChild(cloudSprite, -1);
    }

    this->addChild(_fighter.create(_visibleSize));

    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Fighter::onMouseDown, &_fighter);
    _mouseListener->onMouseUp = CC_CALLBACK_1(Fighter::onMouseUp, &_fighter);
    _mouseListener->onMouseMove = CC_CALLBACK_1(Fighter::onMouseMove, &_fighter);

    _eventDispatcher->addEventListenerWithFixedPriority(_mouseListener, 1);

    scheduleUpdate();

    _nextEnemyTime = NEXT_ENEMY_DELAY;
    _nextTimeAddEnemy = NEXT_TIME_ADD_ENEMY;
    _maxEnemies = 1;

    return true;
}

void HelloWorld::update(float dt)
{
    _fighter.update(dt);


    _nextTimeAddEnemy -= dt;
    if (_nextTimeAddEnemy <= 0) {
        _nextTimeAddEnemy = NEXT_TIME_ADD_ENEMY;
        ++_maxEnemies;
    }

    _nextEnemyTime -= dt;
    if (_nextEnemyTime <= 0 && (_enemies.size() < _maxEnemies)) {
        _nextEnemyTime = NEXT_ENEMY_DELAY;
        std::shared_ptr<Enemy> enemy(EnemyFactory::createEnemy());

        auto sprite = enemy->create(_visibleSize);
        this->addChild(sprite);

        _enemies.push_back(enemy);
    }

    for (auto enemy : _enemies) {
        enemy->update(dt);
        if (!enemy->isVisible()) {
            enemy->reset();
        }
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
