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
    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    scores = Node::create();
    
    auto labelScore = Label::createWithBMFont("fonts/font_score.fnt", "0123");
    labelScore->setBMFontSize(60.0f);
    labelScore->setAlignment(TextHAlignment::CENTER);
    scores->addChild(labelScore, 1);
    
    this->addChild(scores, 0);
    
    return true;
}
