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
    //create new instance pointer
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
    
    // init demon string
    const std::string nameStr = NAME_ARRAY[_nameIndex];
    const std::string wayStr = WAY_ARRAY[_wayIndex];
    
    // create demon sprite
    _demonSprite = Sprite::createWithSpriteFrameName(nameStr + "_" + wayStr + "_stand0001.png");
    
    // invert side when demon go right way
    if(_wayIndex == 2)
    {
        _demonSprite->setScale(-1, 1);
    }
    
    // add demon sprite
    this->addChild(_demonSprite);
    
    return true;
}

void Demon::action(DemonAction demonAction)
{
    // before start new action reset animation
    _demonSprite->stopAction(_demonAction);
    
    // set string init value
    const std::string nameStr = NAME_ARRAY[_nameIndex];
    const std::string wayStr = WAY_ARRAY[_wayIndex];
    
    // select animation (animation name, animation frame number, animation function)
    switch(demonAction)
    {
        case enterDiving:
            setAnimation(createAnimFrames(nameStr + "_back_walk", 6));
            break;
        case waiting:
            setAnimation(createAnimFrames(nameStr + "_" + wayStr + "_stand", 74));
            break;
        case dance:
            setAnimation(createAnimFrames(nameStr + "_" + wayStr + "_dance", 9));
            break;
        case walk:
            setAnimation(createAnimFrames(nameStr + "_" + wayStr + "_walk", 6));
            break;
        case removing:
            setAnimation(createAnimFrames(nameStr + "_remove", 22), removeDemon);
            break;
            
        default:
            break;
    }
}

cocos2d::Vector<cocos2d::SpriteFrame*> Demon::createAnimFrames(std::string animName, int count)
{
    // get sprite cache instance (init in appDelegate)
    auto spriteCache = SpriteFrameCache::getInstance();
    
    // create animation frame array
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    
    // format frame name to char array, add frame number and image extention
    std::string s = animName + "%04d.png";
    unsigned long n = s.length();
    char char_anim[n + 1];
    strcpy(char_anim, s.c_str());
    
    // fill animation array
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        // add frame name number
        sprintf(str,char_anim,i);
        
        // push sprite frame in animation vector
        auto sprite = spriteCache->getSpriteFrameByName(str);
        if(sprite != nullptr)
        {
            animFrames.pushBack(sprite);
        }
    }
    
    return animFrames;
}

bool Demon::setAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> animFrames, DemonActionFunc animFunc)
{
    // set animation FPS
    auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 24);
    
    // init action pointer
    _demonAction = nullptr;
    
    // merge animation and function to ation pointer
    switch (animFunc) {
        case repeatAninForever:
            // repeat animation forever
            _demonAction = RepeatForever::create(Animate::create(animation));
            break;
        case removeDemon:
            // send remove remove event when animation finished
            _demonAction = Sequence::create(Animate::create(animation), CallFunc::create([=](){
                _eventDispatcher->dispatchCustomEvent(_name + "_REMOVE_END");
            }), NULL);
        break;
            
        default:
            break;
    }
    
    // run demon action
    _demonSprite->runAction(_demonAction);
    
    return true;
}

void Demon::setDemonGridPosition(int line, int collumn)
{
    _line = line;
    _collumn = collumn;
}

DemonPosition Demon::getDemonGridPosition()
{
    DemonPosition demonPosition;
    demonPosition.line = _line;
    demonPosition.collumn = _collumn;
    
    return demonPosition;
}

DemonPosition Demon::getDemonGridWayPosition()
{
    int wayL = _line;
    int wayC = _collumn;
    
    switch (_wayIndex) {
        case 0: wayL +=1; break; // up
        case 1: wayC -=1; break; // left
        case 2: wayC +=1; break; // right
        case 3: wayL -=1; break; // down
        default: break;
    }
    
    DemonPosition demonPosition;
    demonPosition.line = wayL;
    demonPosition.collumn = wayC;
    
    return demonPosition;
}

void Demon::displayScore(int score)
{
    // create score label and place over demon
    auto labelScore = Label::createWithBMFont("fonts/font_combo.fnt", std::to_string(score));
    float labelScoreSize = 36.0f;
    labelScore->setBMFontSize(labelScoreSize);
    labelScore->setAlignment(TextHAlignment::CENTER);
    labelScore->setPosition(Vec2(0, labelScoreSize));
    
    this->addChild(labelScore,1);
    
    // init label score end position
    Vec2 scoreMovePos = Vec2(0, _demonSprite->getContentSize().height/2);
    
    // create label score action
    auto move = MoveTo::create(SCORE_MOVE_TIME, scoreMovePos);
    auto fade = FadeTo::create(SCORE_MOVE_TIME, 0);
    auto callFunc = CallFunc::create([labelScore]()
    {
        labelScore->removeFromParent();
    });
    
    // run action
    auto seq = Sequence::create(Spawn::create(move, fade, NULL), callFunc, NULL);
    labelScore->runAction(seq);
    
}

int Demon::getNameIndex()
{
    return _nameIndex;
}
int Demon::getWayIndex()
{
    return _wayIndex;
}
int Demon::getPositionIndex()
{
    return _line * 10 + _collumn;
}
