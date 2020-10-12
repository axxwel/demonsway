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
        _demonsGrid[l][c] = demon;
        moveDemonsGrid();
    });
    auto seq = Sequence::create(Spawn::create(scaleSeq, move, NULL), callFunc, NULL);
    demon->runAction(seq);
    demon->action(dance);
    
    return true;
}

bool DisplayDemonsGrid::moveDemonsGrid()
{
    bool noDemonsMoved = true;
    
    for(int l = 0; l < GRID_SIZE; l++)
    {
        for(int c = 0; c < GRID_SIZE; c++)
        {
            Demon* demon = _demonsGrid[l][c];
            if(demon)
            {
                // set moving grid case new line (int newL), new collumn (int newC)
                int wayIndex = demon->getWayIndex();
                int newL = l;
                int newC = c;
                switch (wayIndex) {
                    case 0: newL +=1; break;
                    case 1: newC -=1; break;
                    case 2: newC +=1; break;
                    case 3: newL -=1; break;
                        
                    default: break;
                }
                
                // check if new case is out of grid
                if(newL >= 0 && newL < GRID_SIZE && newC >= 0 && newC < GRID_SIZE)
                {
                    // check if new case is free
                    if(_demonsGrid[newL][newC] == nullptr)
                    {
                        // check if moving demon had already moved
                        bool demonAlreadyMoved = false;
                        Vector<Demon*>::iterator dIt;
                        for(dIt = _demonsMovedList.begin(); dIt != _demonsMovedList.end(); dIt++)
                        {
                            if(demon == *dIt)
                            {
                                demonAlreadyMoved = true;
                            }
                        }
                        if(demonAlreadyMoved == false)
                        {
                            // if all flags ok move demon and push it in already moved list.
                            noDemonsMoved = false;
                            _demonsMovedList.push_back(demon);
                            moveDemon(demon, l, c, newL, newC);
                        }
                    }
                }
            }
        }
    }
    
    // check if all demon moved
    if(noDemonsMoved)
    {
        _demonsMovedList.clear();
        addNewDemon();
    }
    else
    {
        float delay = MOVE_TIME + 0.1;
        auto delayTime = DelayTime::create(delay);
        auto callFunc = CallFunc::create([this](){
            moveDemonsGrid();
        });
        this->runAction(Sequence::create(delayTime, callFunc, NULL));
    }
    
    return true;
}

bool DisplayDemonsGrid::moveDemon(Demon* demon, int oldL, int oldC, int newL, int newC)
{
    if(!demon)
        return false;
    
    //get demon grid pixel position
    Vec2 posDemon = StaticGrid::getPositionXY(Vec2(newL, newC));
    
    // move demon to grid position and refresh grid
    auto move = MoveTo::create(MOVE_TIME, posDemon);
    auto callFunc = CallFunc::create([=]()
    {
        demon->action(waiting);
        _demonsGrid[newL][newC] = demon;
        _demonsGrid[oldL][oldC] = nullptr;
    });
    auto seq = Sequence::create(move, callFunc, NULL);
    demon->runAction(seq);
    demon->action(walk);
    
    return true;
}
