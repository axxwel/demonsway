//
//  HomeScene.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 15/09/2020.
//

#include "HomeScene.hpp"

USING_NS_CC;

Scene* HomeScene::createScene()
{
    return HomeScene::create();
}

// init scene
bool HomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    return true;
}
