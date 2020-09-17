//
//  HomeScene.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 15/09/2020.
//

#include "HomeScene.hpp"

#include "../DisplayObjects/DisplayBackground.hpp"

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

    // add sprite sheet image list
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameScreenAssets.plist");

    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
    // create and add displayBackground
    auto background = DisplayBackground::create();
    background->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                     visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

    // create and add title image
    auto title = Sprite::createWithSpriteFrameName("title@2x.png");
    title->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                visibleSize.height*2/3 + origin.y));
    this->addChild(title, 1);
        
    // create start button images, add to menu and place
    auto startBtnNormal = Sprite::createWithSpriteFrameName("button_start_normal@2x.png");
    auto startBtnSelected = Sprite::createWithSpriteFrameName("button_start_selected@2x.png");
    auto startBtn = MenuItemSprite::create(
                                               startBtnNormal,
                                               startBtnSelected,
                                               CC_CALLBACK_1(HomeScene::menuPlayCallback, this));
        
    startBtn->setPosition(Vec2(
                                origin.x + visibleSize.width*1/4,
                                title->getPosition().y - title->getContentSize().height/2 - startBtn->getContentSize().height/2));
        
    // create score button images, add to menu and place
    auto scoreBtnNormal = Sprite::createWithSpriteFrameName("button_score_normal@2x.png");
    auto scoreBtnSelected = Sprite::createWithSpriteFrameName("button_score_selected@2x.png");
    auto scoreBtn = MenuItemSprite::create(
                                            scoreBtnNormal,
                                            scoreBtnSelected,
                                            CC_CALLBACK_1(HomeScene::menuScoresCallback, this));
        
    scoreBtn->setPosition(Vec2(
                                origin.x + visibleSize.width*3/4,
                                title->getPosition().y - title->getContentSize().height/2 - startBtn->getContentSize().height/2));
        
    // create sound button images, add to menu and place
    auto soundBtnNormal = Sprite::createWithSpriteFrameName("sound_on@2x.png");
    auto soundBtnSelected = Sprite::createWithSpriteFrameName("sound_off@2x.png");
    auto soundBtn = MenuItemSprite::create(
                                              soundBtnNormal,
                                              soundBtnSelected,
                                              CC_CALLBACK_1(HomeScene::menuSoundCallback, this));

    soundBtn->setPosition(Vec2(
                                origin.x + visibleSize.width - soundBtn->getContentSize().width/2,
                                origin.y + visibleSize.height - soundBtn->getContentSize().height/2));
        

    // create, place and add menu
    auto menu = Menu::create(startBtn, scoreBtn, soundBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
        
    return true;
}

// replace current scene to game scene
void HomeScene::menuPlayCallback(Ref* pSender)
{
    /*
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
    */
}

// replace current scene to score scene
void HomeScene::menuScoresCallback(Ref* pSender)
{
    /*
    auto scene = ScoreScene::createScene();
    Director::getInstance()->replaceScene(scene);
    */
}

//change sound value
void HomeScene::menuSoundCallback(Ref* pSender)
{
    
}
