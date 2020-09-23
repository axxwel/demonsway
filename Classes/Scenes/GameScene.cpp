//
//  GameScene.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#include "HomeScene.hpp"
#include "GameScene.hpp"

#include "../DisplayObjects/DisplayBackground.hpp"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// init scene
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameScreenAssets.plist");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add exit button
    auto exitBtnNormal = Sprite::createWithSpriteFrameName("exit_normal@2x.png");
    auto exitBtnSelected = Sprite::createWithSpriteFrameName("exit_selected@2x.png");
    auto exitBtn = MenuItemSprite::create(
                                           exitBtnNormal,
                                           exitBtnSelected,
                                           CC_CALLBACK_1(GameScene::menuHomeCallback, this));

    float x = origin.x + exitBtn->getContentSize().width/2;
    float y = origin.y + visibleSize.height - exitBtn->getContentSize().height/2;
    exitBtn->setPosition(Vec2(x,y));

    // create menu, it's an autorelease object
    auto menu = Menu::create(exitBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // add "background"
    auto background = DisplayBackground::create();
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

    // add "grid"
    gridDisplay = DisplayGrid::create();
    this->addChild(gridDisplay, 1);
    
    //add "divingBoard"
    divingBoard = Sprite::createWithSpriteFrameName("divingBoard@2x.png");
    divingBoard->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + divingBoard->getContentSize().height/2));
    this->addChild(divingBoard);
    
    _eventDispatcher->addCustomEventListener("GRID_BTN_PUSH",[=](EventCustom* event)
    {
        std::vector<int>* eventDataPtr = static_cast<std::vector<int>*>(event->getUserData());
        std::vector<int> eventData = *eventDataPtr;
        int line = eventData[0];
        int collumn = eventData[1];
        
        printf("dataEvent l = %i, c = %i\n", line, collumn);
    });
    
    return true;
}

void GameScene::menuHomeCallback(Ref* pSender)
{
    auto scene = HomeScene::createScene();
    Director::getInstance()->replaceScene(scene);

}
