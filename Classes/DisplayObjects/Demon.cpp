//
//  Demon.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#include "Demon.hpp"

USING_NS_CC;

Demon* Demon::create()
{
    Demon* ret = new (std::nothrow) Demon();
    if(ret && ret->init ())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}


bool Demon::init()
{
    srand((unsigned)time(NULL));
    nameIndex = rand() % 9;
    wayIndex = rand() % 4;
    
    nameStr = "Water"; //NAME_ARRAY[nameIndex];
    wayStr = "face"; //WAY_ARRAY[wayIndex];
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("demonWaterAssets.plist");
    
    demonSprite = Sprite::createWithSpriteFrameName(wayStr + "_stand0001.png");
    this->addChild(demonSprite);
    
    return true;
}

bool Demon::action(DemonAction demonAction)
{
    demonSprite->stopAllActions();
    
    switch(demonAction)
    {
        case enterDiving : setAnimation("back_walk", 6); break;
        case waiting     : setAnimation(wayStr + "_stand", 74);break;
        case dance       : setAnimation(wayStr + "_dance", 9);break;
        case walk        : setAnimation(wayStr + "_walk", 6);break;
        default          : break;
    }
    return true;
}

bool Demon::setAnimation(std::string anim, int count)
{
    auto spriteCache = SpriteFrameCache::getInstance();
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        char* imageNbr;
        std::string str = anim + "%04d.png";
        sprintf(imageNbr,str.c_str(),i);
        
        auto sprite = spriteCache->getSpriteFrameByName(imageNbr);
        if(sprite != nullptr)
        {
            animFrames.pushBack(sprite);
        }
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 24);
    demonSprite->runAction(RepeatForever::create(Animate::create(animation)));
    
    return true;
}
