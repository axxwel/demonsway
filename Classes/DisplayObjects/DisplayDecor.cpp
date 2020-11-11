//
//  DisplayDecor.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 07/11/2020.
//

#include "DisplayDecor.hpp"

USING_NS_CC;

DisplayDecor* DisplayDecor::create()
{
    //create new instance pointer
    DisplayDecor* ret = new (std::nothrow) DisplayDecor();
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

bool DisplayDecor::init()
{
    _decor = Node::create();
    
    //import redBelt image
    auto redBelt = Sprite::createWithSpriteFrameName("belt_red@2x.png");
    redBelt->setPosition(Vec2(0, 104));
    
    _decor->addChild(redBelt, 0);
    
    //import redBelt image
    auto yellowBelt = Sprite::createWithSpriteFrameName("belt_yellow@2x.png");
    yellowBelt->setPosition(Vec2(0, -104));
    
    _decor->addChild(yellowBelt, 0);
    
    this->addChild(_decor);
    
    return true;
}

void DisplayDecor::addTitle()
{
    // create and add title image
    auto title = Sprite::createWithSpriteFrameName("title@2x.png");
    _decor->addChild(title, 1);
}

void DisplayDecor::addScores(int score, int combo)
{
    // create and place score label
    auto labelScore = Label::createWithBMFont("fonts/font_score.fnt", std::to_string(score));
    float labelScoreSize = 120.0f;
    labelScore->setBMFontSize(labelScoreSize);
    labelScore->setAlignment(TextHAlignment::CENTER);
    labelScore->setPosition(Vec2(0, 104));
    
    _decor->addChild(labelScore, 1);
    
    // create and place combo label
    auto labelCombo = Label::createWithBMFont("fonts/font_combo.fnt", std::to_string(combo));
    float labelComboSize = 72.0f;
    labelCombo->setBMFontSize(labelComboSize);
    labelCombo->setAlignment(TextHAlignment::CENTER);
    labelCombo->setColor(Color3B::YELLOW);
    labelCombo->setPosition(Vec2(0, - 104));
    
    _decor->addChild(labelCombo, 1);
}

void DisplayDecor::moveDecor()
{
    //MOVE DECOR
}
