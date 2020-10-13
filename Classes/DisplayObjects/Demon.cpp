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
    _nameIndex = rand() % 9;
    _wayIndex = rand() % 4;
    
    const std::string nameStr = NAME_ARRAY[_nameIndex];
    const std::string wayStr = WAY_ARRAY[_wayIndex];
    
    // create demon
    _demonSprite = Sprite::createWithSpriteFrameName(nameStr + "_" + wayStr + "_stand0001.png");
    
    // invert side when demon go right
    if(_wayIndex == 2)
    {
        _demonSprite->setScale(-1, 1);
    }
    
    // add demon
    this->addChild(_demonSprite);
    
    return true;
}

bool Demon::action(DemonAction demonAction)
{
    // before start new action reset animation
    _demonSprite->stopAllActions();
    
    const std::string nameStr = NAME_ARRAY[_nameIndex];
    const std::string wayStr = WAY_ARRAY[_wayIndex];
    
    // select animation (animetion name, animation frame number)
    switch(demonAction)
    {
        case enterDiving : setAnimation(nameStr + "_back_walk", 6); break;
        case waiting     : setAnimation(nameStr + "_" + wayStr + "_stand", 74);break;
        case dance       : setAnimation(nameStr + "_" + wayStr + "_dance", 9);break;
        case walk        : setAnimation(nameStr + "_" + wayStr + "_walk", 6);break;
        case removing      : setAnimation(nameStr + "_remove", 22);break;
            
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
    _demonSprite->runAction(RepeatForever::create(Animate::create(animation)));
    
    return true;
}

int Demon::getNameIndex()
{
    return _nameIndex;
}
int Demon::getWayIndex()
{
    return _wayIndex;
}
