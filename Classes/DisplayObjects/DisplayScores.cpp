//
//  DisplayScores.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 28/10/2020.
//

#include "DisplayScores.hpp"

USING_NS_CC;

DisplayScores* DisplayScores::create()
{
    //create new instance pointer
    DisplayScores* ret = new (std::nothrow) DisplayScores();
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

bool DisplayScores::init()
{
    //get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    scores = Node::create();
    /*
    cocos2d::Label* label = cocos2d::Label::createWithTTF("Hello World!","Resources/fonts/Marker Felt.ttf",45);
    label->setPosition(0,0);
    this->addChild(label, 1);
   
    auto labelScore = Label::createWithBMFont("font_score.fnt", "000");
    labelScore->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
    scores->addChild(labelScore, 1);
    scores->addChild(labelScore);
    */
    this->addChild(scores, 0);
    
    
    return true;
}
