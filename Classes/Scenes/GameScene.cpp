//
//  GameScene.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#include "HomeScene.hpp"
#include "GameScene.hpp"

#include "../DisplayObjects/DisplayBackground.hpp"
#include "../DisplayObjects/DisplayDecor.hpp"

#include "../Models/StaticSounds.hpp"

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
    
    // create, place and add sccore
    _scoresDisplay = DisplayScores::create();
    _scoresDisplay->setPosition(Vec2(visibleSize.width/2 + origin.x, (visibleSize.height * 3 + StaticGrid::getGridSize().height)/4));
    this->addChild(_scoresDisplay, 3);
    
    // create and add display grid (display grid use static grid to set position)
    _gridDisplay = DisplayGrid::create();
    this->addChild(_gridDisplay, 1);
    
    // create and add divingBoard
    _divingBoard = Sprite::createWithSpriteFrameName("divingBoard@2x.png");
    _divingBoard->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + _divingBoard->getContentSize().height/2));
    this->addChild(_divingBoard,2);
    
    // create and add display grid (display grid use static grid to set position)
    auto demonsGridDisplay = DisplayDemonsGrid::create(_divingBoard);
    this->addChild(demonsGridDisplay, 3);
    
    // remove events listeners (create duplicate when restart a new GameScene)
    _eventDispatcher->removeCustomEventListeners("GRID_BTN_PUSH");
    _eventDispatcher->removeCustomEventListeners("DEMON_MOVED");
    _eventDispatcher->removeCustomEventListeners("DEMON_REMOVED");
    _eventDispatcher->removeCustomEventListeners("END_ACTION_GRID");
    _eventDispatcher->removeCustomEventListeners("GAME_OVER");
    _eventDispatcher->removeCustomEventListeners("ALL_DEMONS_REMOVED");
    
    //add event listener to check whitch button is pushed in displayGrid
    _eventDispatcher->addCustomEventListener("GRID_BTN_PUSH",[=](EventCustom* event)
    {
        std::vector<int>* eventDataPtr = static_cast<std::vector<int>*>(event->getUserData());
        std::vector<int> eventData = *eventDataPtr;
        int buttonLine = eventData[0];
        int buttonCollumn = eventData[1];
        
        demonsGridDisplay->addDemonGrid(buttonLine, buttonCollumn);
    });
    
    //add event listener to check when demon was move in grid
    _eventDispatcher->addCustomEventListener("DEMON_MOVED",[this](EventCustom* event)
    {
        _scoresDisplay->addToCombo(1);
    });
    
    //add event listener to check when demon was remove in grid
    _eventDispatcher->addCustomEventListener("DEMON_REMOVED",[this](EventCustom* event)
    {
        _scoresDisplay->addToCombo(3);
    });
    
    //add event listener to check when all actions ended and new demon added in diving board
    _eventDispatcher->addCustomEventListener("END_ACTION_GRID",[this](EventCustom* event)
    {
        _scoresDisplay->setScore();
    });
    
    //add event listener to check when demon grid was full
    _eventDispatcher->addCustomEventListener("GAME_OVER",[=](EventCustom* event)
    {
        StaticSounds::playSound("game_over");
        gameOverStartCallback();
    });
    
    //add event listener to check when all demons was removed after game over
    _eventDispatcher->addCustomEventListener("ALL_DEMONS_REMOVED",[=](EventCustom* event)
    {
        StaticSounds::playSound("aplause");
        
        // create start button images, add to menu and place
        auto okBtnNormal = Sprite::createWithSpriteFrameName("button_ok_normal@2x.png");
        auto okBtnSelected = Sprite::createWithSpriteFrameName("button_ok_selected@2x.png");
        auto okBtn = MenuItemSprite::create(
                                                   okBtnNormal,
                                                   okBtnSelected,
                                                   CC_CALLBACK_1(GameScene::menuGameCallback, this));
            
        okBtn->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 1/4 + origin.y));
        menu->addChild(okBtn);
        
        gameOverEndCallback();
    });
    
    /*
    // play home theme music;
    StaticSounds::playMusic("game");
    */
    
    return true;
}

// replace current scene to home scene
void GameScene::menuHomeCallback(Ref* pSender)
{
    StaticSounds::playSound("window");
    auto scene = HomeScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

// replace current scene to home scene
void GameScene::menuGameCallback(Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameScene::gameOverStartCallback()
{
    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create and add displayDecor
    auto decor = DisplayDecor::create();
    ScoresNumber scoresNumber = _scoresDisplay->getScore();
    decor->addScores(scoresNumber.score, scoresNumber.combo);
    decor->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 2/3 + origin.y));
    this->addChild(decor, 4);
    
    
    _scoresDisplay->removeFromParent();
}

void GameScene::gameOverEndCallback()
{
    _divingBoard->removeFromParent();
    _gridDisplay->removeFromParent();
}
