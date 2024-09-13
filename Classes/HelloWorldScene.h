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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "nodes/Background.h"
#include "nodes/Fighter.h"
#include "nodes/Enemy.h"
#include "nodes/Meteor.h"
#include "GameEngine.h"

#include "cocos2d.h"

#include <list>

class HelloWorld : public cocos2d::Layer
{
    std::shared_ptr<GameEngine> _gameEngine;

    cocos2d::EventListenerMouse *_mouseListener = nullptr;
    cocos2d::Size _visibleSize;
    Background _background;
    Fighter _fighter;
    Meteor _meteor;
    float _nextTimeShowMeteor;
    cocos2d::Label* _gameOverLabel = nullptr;
    cocos2d::Menu* _restartButton = nullptr;
    int _oldScore = 0;
    cocos2d::Label* _score = nullptr;
    float _scoreXOffset = 0.f;
    float _scoreY = 0.f;


    void reset();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void restartGameButtonPressed(cocos2d::Ref* pSender);
    void update(float dt);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
