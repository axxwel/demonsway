//
//  GameScene.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#include "HomeScene.hpp"
#include "GameScene.hpp"

#include "../Models/StaticGrid.hpp"

#include "../DisplayObjects/DisplayBackground.hpp"
#include "../DisplayObjects/DisplayGrid.hpp"


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
    
    // get sprite sheet image list
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameScreenAssets.plist");

    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create and add displayBackground
    auto background = DisplayBackground::create();
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

    // create sound button images, add to menu and place
    auto exitBtnNormal = Sprite::createWithSpriteFrameName("exit_normal@2x.png");
    auto exitBtnSelected = Sprite::createWithSpriteFrameName("exit_selected@2x.png");
    auto exitBtn = MenuItemSprite::create(
                                           exitBtnNormal,
                                           exitBtnSelected,
                                           CC_CALLBACK_1(GameScene::menuHomeCallback, this));

    float x = origin.x + exitBtn->getContentSize().width/2;
    float y = origin.y + visibleSize.height - exitBtn->getContentSize().height/2;
    exitBtn->setPosition(Vec2(x,y));

    // create, place and add menu
    auto menu = Menu::create(exitBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // create and add display grid (display grid use static grid to set position)
    auto gridDisplay = DisplayGrid::create();
    this->addChild(gridDisplay, 1);
    
    // create and add divingBoard
    divingBoard = Sprite::createWithSpriteFrameName("divingBoard@2x.png");
    divingBoard->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + divingBoard->getContentSize().height/2));
    this->addChild(divingBoard);
    
    addNewDemon();
    
    //add event listener to check whitch button is pushed in displayGrid
    _eventDispatcher->addCustomEventListener("GRID_BTN_PUSH",[=](EventCustom* event)
    {
        std::vector<int>* eventDataPtr = static_cast<std::vector<int>*>(event->getUserData());
        std::vector<int> eventData = *eventDataPtr;
        int buttonLine = eventData[0];
        int buttonCollumn = eventData[1];
        
        printf("dataEvent l = %i, c = %i\n", buttonLine, buttonCollumn);
        addDemonGrid(buttonLine, buttonCollumn);
    });
    
    return true;
}

bool GameScene::addNewDemon()
{
    demonDiver = nullptr;
    
    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto newDemon = Demon::create();
    newDemon->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y - newDemon->getContentSize().height));
    this->addChild(newDemon, 2);
    
    auto move = MoveTo::create(MOVE_TIME, Vec2(divingBoard->getPosition().x,divingBoard->getContentSize().height*3/4));
    auto callFunc = CallFunc::create([=]()
    {
        newDemon->action(waiting);
        demonDiver = newDemon;
    });
    auto seq = Sequence::create(move, callFunc, NULL);
    newDemon->runAction(seq);
    newDemon->action(enterDiving);
    
    return true;
}

bool GameScene::addDemonGrid(int l, int c)
{
    if(!demonDiver)
        return false;
    
    Demon* demon = demonDiver;
    addNewDemon();
    
    Vec2 posDemon = StaticGrid::getPositionXY(Vec2(l, c));
    
    auto move = MoveTo::create(MOVE_TIME, posDemon);
    auto scaleUp = ScaleTo::create(MOVE_TIME/2, 1.5);
    auto scaleDown = ScaleTo::create(MOVE_TIME/2, 0.8);
    auto scaleSeq = Sequence::create(scaleUp, scaleDown, NULL);
    auto callFunc = CallFunc::create([=]()
    {
        demon->action(waiting);
        //ADD TO DEMON GRID
    });
    auto seq = Sequence::create(Spawn::create(scaleSeq, move, NULL), callFunc, NULL);
    demon->runAction(seq);
    demon->action(dance);
    
    return true;
}

// replace current scene to home scene
void GameScene::menuHomeCallback(Ref* pSender)
{
    auto scene = HomeScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
