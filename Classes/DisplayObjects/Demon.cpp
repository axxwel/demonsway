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
    // init demon random type and direction
    srand((unsigned)time(NULL));
    nameIndex = 1;//rand() % 9;
    wayIndex = 0;//rand() % 4;
    
    const std::string nameStr = NAME_ARRAY[nameIndex];
    const std::string wayStr = WAY_ARRAY[wayIndex];
    
    // create and add demon
    demonSprite = Sprite::createWithSpriteFrameName(nameStr + "_" + wayStr + "_stand0001.png");
    this->addChild(demonSprite);
    
    return true;
}

bool Demon::action(DemonAction demonAction)
{
    // before start new action reset animation
    demonSprite->stopAllActions();
    
    const std::string nameStr = NAME_ARRAY[nameIndex];
    const std::string wayStr = WAY_ARRAY[wayIndex];
    
    // select animation (animetion name, animation frame number)
    switch(demonAction)
    {
        case enterDiving : setAnimation(nameStr + "_back_walk", 6); break;
        case waiting     : setAnimation(nameStr + "_" + wayStr + "_stand", 74);break;
        case dance       : setAnimation(nameStr + "_" + wayStr + "_dance", 9);break;
        case walk        : setAnimation(nameStr + "_" + wayStr + "_walk", 6);break;
        default          : break;
    }
    return true;
}

bool Demon::setAnimation(std::string animName, int count)
{
    // get sprite cache instance (init in appDelegate)
    auto spriteCache = SpriteFrameCache::getInstance();
    
    // create animation frame vector
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    
    // format frame name
    char* imageNbr;
    std::string str = animName + "%04d.png";
    
    for(int i = 1; i <= count; i++)
    {
        // set frame name number
        sprintf(imageNbr,str.c_str(),i);
        
        // push sprite frame in animation vector
        auto sprite = spriteCache->getSpriteFrameByName(imageNbr);
        if(sprite != nullptr)
        {
            
            animFrames.pushBack(sprite);
        }
    }
    
    // set animation FPS and run animation
    auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 24);
    demonSprite->runAction(RepeatForever::create(Animate::create(animation)));
    
    return true;
}
