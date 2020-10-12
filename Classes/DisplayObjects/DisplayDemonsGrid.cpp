//
//  DisplayDemonsGrid.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 12/10/2020.
//

#include "DisplayDemonsGrid.hpp"

#include "../Models/StaticGrid.hpp"

USING_NS_CC;

DisplayDemonsGrid* DisplayDemonsGrid::create(cocos2d::Sprite* divingBoard)
{
    //create new instance pointer
    DisplayDemonsGrid* ret = new (std::nothrow) DisplayDemonsGrid();
    if(ret && ret->init (divingBoard))
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

bool DisplayDemonsGrid::init(cocos2d::Sprite* divingBoard)
{
    //init diving board pointer
    _divingBoard = divingBoard;
    
    //clean demons arrays
    _demonsMovedList.clear();
    _demonsGrid.clear();
    
    //init new demon grid
    for(int l = 0; l < GRID_SIZE; l++)
    {
        std::vector<Demon*> demonGridLine;
        for(int c = 0; c < GRID_SIZE; c++)
        {
            demonGridLine.push_back(nullptr);
        }
        _demonsGrid.push_back(demonGridLine);
    }
    
    addNewDemon();
    
    return true;
}

bool DisplayDemonsGrid::addNewDemon()
{
    // reset the demon diver pointer
    _demonDiver = nullptr;
    
    // get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create new demon and add out of screen
    auto newDemon = Demon::create();
    newDemon->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y - newDemon->getContentSize().height));
    this->addChild(newDemon, 2);
    
    // move demon to divin board edge an wait push grid button
    auto move = MoveTo::create(MOVE_TIME, Vec2(_divingBoard->getPosition().x,_divingBoard->getContentSize().height*3/4));
    auto callFunc = CallFunc::create([=]()
    {
        newDemon->action(waiting);
        _demonDiver = newDemon;
    });
    auto seq = Sequence::create(move, callFunc, NULL);
    newDemon->runAction(seq);
    newDemon->action(enterDiving);
    
    return true;
}

bool DisplayDemonsGrid::addDemonGrid(int l, int c)
{
    //check if a demon is ready to jump in demon grid
    if(!_demonDiver)
        return false;
    
    // init jumper demon pointer
    Demon* demon = _demonDiver;
    
    //get demon grid pixel position
    Vec2 posDemon = StaticGrid::getPositionXY(Vec2(l, c));
    
    // move demon to grid position
    auto move = MoveTo::create(MOVE_TIME, posDemon);
    auto scaleUp = ScaleTo::create(MOVE_TIME/2, JUMP_SCALE);
    auto scaleDown = ScaleTo::create(MOVE_TIME/2, DEMON_IN_GRID_SCALE);
    auto scaleSeq = Sequence::create(scaleUp, scaleDown, NULL);
    auto callFunc = CallFunc::create([=]()
    {
        demon->action(waiting);
        //ADD TO DEMON GRID
    });
    auto seq = Sequence::create(Spawn::create(scaleSeq, move, NULL), callFunc, NULL);
    demon->runAction(seq);
    demon->action(dance);
    
    return true;
}
