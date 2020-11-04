//
//  DisplayScores.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 28/10/2020.
//

#include "DisplayScores.hpp"

#include "../Models/StaticGrid.hpp"

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
    _score = 0;
    _combo = 0;
    
    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // init scores container node
    scores = Node::create();
    
    // create and place score label
    _labelScore = Label::createWithBMFont("fonts/font_score.fnt", std::to_string(_score));
    float labelScoreSize = 60.0f;
    _labelScore->setBMFontSize(labelScoreSize);
    _labelScore->setAlignment(TextHAlignment::CENTER);
    _labelScore->setPosition(Vec2(0, labelScoreSize * 3/4));
    
    scores->addChild(_labelScore, 0);
    
    // create and place combo label
    _labelCombo = Label::createWithBMFont("fonts/font_combo.fnt", std::to_string(_combo));
    float labelComboSize = 36.0f;
    _labelCombo->setBMFontSize(labelComboSize);
    _labelCombo->setAlignment(TextHAlignment::CENTER);
    _labelCombo->setColor(Color3B::YELLOW);
    _labelCombo->setPosition(Vec2(0, - labelComboSize * 3/4));
    _labelCombo->setOpacity(0);
    
    scores->addChild(_labelCombo, 1);
    
    this->addChild(scores, 0);
    
    return true;
}

void DisplayScores::addToCombo(int combo)
{
    _combo += combo;
    
    // display combo label
    _labelCombo->setOpacity(255);
    _labelCombo->setString(std::to_string(_combo));
}

void DisplayScores::setScore()
{
    _score += _combo;
    _combo = 0;
    
    // keep combo label initial position
    Vec2 initComboPos = _labelCombo->getPosition();
    
    // create animation to add combo label to score label
    auto move = MoveTo::create(COMBO_MOVE_TIME, _labelScore->getPosition());
    auto fade = FadeTo::create(COMBO_MOVE_TIME, 0);
    auto callFunc = CallFunc::create([this, initComboPos]()
    {
        _labelCombo->setPosition(initComboPos);
        _labelScore->setString(std::to_string(_score));
    });
    
    // run action
    auto seq = Sequence::create(Spawn::create(move, fade, NULL), callFunc, NULL);
    _labelCombo->runAction(seq);
}
