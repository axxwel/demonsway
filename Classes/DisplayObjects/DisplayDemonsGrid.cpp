//
//  DisplayDemonsGrid.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 12/10/2020.
//

#include "DisplayDemonsGrid.hpp"

#include "../Models/StaticGrid.hpp"
#include "../Models/StaticTest.hpp"

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
    _demonsActionList.clear();
    _demonsInGridList.clear();
    
    // add new random demon on diving board
    addNewDemonDiver();
    
    return true;
}

bool DisplayDemonsGrid::addDemonGrid(int l, int c)
{
    // check if demon is ready to jump in demon grid
    if(!_demonDiver)
        return false;
    
    // check if demon grid case is free
    if(!StaticTest::getCaseFree(l, c, _demonsInGridList))
        return false;
    
    // init jumper demon pointer
    Demon* demon = _demonDiver;
    
    // reset the demon diver pointer
    _demonDiver = nullptr;
    
    // get grid pixel position
    Vec2 posDemon = StaticGrid::getPositionXY(Vec2(l, c));
    
    // demon jump to grid position
    auto move = MoveTo::create(MOVE_TIME, posDemon);
    auto scaleUp = ScaleTo::create(MOVE_TIME/2, JUMP_SCALE);
    auto scaleDown = ScaleTo::create(MOVE_TIME/2, DEMON_IN_GRID_SCALE);
    auto scaleSeq = Sequence::create(scaleUp, scaleDown, NULL);
    auto callFunc = CallFunc::create([=]()
    {
        demon->action(waiting);
        setInGrid(demon, l, c);
        startActionGrid();
    });
    auto seq = Sequence::create(Spawn::create(scaleSeq, move, NULL), callFunc, NULL);
    demon->runAction(seq);
    demon->action(dance);
    
    return true;
}

bool DisplayDemonsGrid::addNewDemonDiver()
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

void DisplayDemonsGrid::startActionGrid(int actionTurn)
{
    _actionTurn = actionTurn;
    
    if(_actionTurn <= 0)
    {
        printf("START_ACTION===========================\n");
        _demonsActionList.clear();
        
        _demonsActionList.insert(_demonsActionList.begin(), _demonsInGridList.begin(), _demonsInGridList.end());
    }
    
    printf("turn(start) = %i\n", _actionTurn);
    
    bool demonMoved = moveDemonsGrid();
    
    if(_demonsActionList.size() <= 0 || !demonMoved)
    {
        printf("END_ACTION=================================\n");
        _actionTurn = 0;
        addNewDemonDiver();
    }
    else
    {
        printf("LISTENER_END_TURN\n");
        _actionTurn ++;
        _eventDispatcher->addCustomEventListener("DEMONS_ANIMATIONS_ENDS",[this](EventCustom* event)
        {
            printf("END_TURN\n");
            _eventDispatcher->removeCustomEventListeners("DEMONS_ANIMATIONS_ENDS");
            printf("turn(end) = %i\n", _actionTurn);
            startActionGrid(_actionTurn);
        });
    }
}

bool DisplayDemonsGrid::moveDemonsGrid()
{
    // is a demon move boolean init
    bool demonMoved = false;
    
    // init demon can move list
    _demonsToMoveList.clear();
    std::vector<Demon*>::iterator moveIt;
    _demonsToMoveList = StaticTest::getMoveDemonList(_demonsActionList, _demonsInGridList);
    
    
    for(moveIt = _demonsToMoveList.begin(); moveIt != _demonsToMoveList.end(); moveIt++)
    {
        demonMoved = true;
        
        // move demon of the list
        Demon* movingDemon = *moveIt;
        moveDemon(movingDemon);
        
        // remove demon from the action list
         _demonsActionList.erase(std::find(_demonsActionList.begin(), _demonsActionList.end(), movingDemon));
    }
    
    return demonMoved;
}

bool DisplayDemonsGrid::moveDemon(Demon* demon)
{
    //get demon grid pixel position
    DemonPosition demonWayPos = demon->getDemonGridWayPosition();
    const int newL = demonWayPos.line;
    const int newC = demonWayPos.collumn;
    Vec2 posDemon = StaticGrid::getPositionXY(Vec2(newL, newC));
    
    // move demon to grid position
    auto move = MoveTo::create(MOVE_TIME, posDemon);
    auto callFunc = CallFunc::create([demon,newL,newC,this]()
    {
        // init action ended
        demon->action(waiting);
        setInGrid(demon, newL, newC);
        
        // remove demon from move list
        _demonsToMoveList.erase(std::find(_demonsToMoveList.begin(), _demonsToMoveList.end(), demon));
        
        // test if is the last action
        areDemonsAnimationsEnds();
    });
    
    // run action
    auto seq = Sequence::create(move, callFunc, NULL);
    demon->runAction(seq);
    demon->action(walk);
    
    return true;
}

void DisplayDemonsGrid::setInGrid(Demon* demon, int line, int collumn)
{
    // init demon : name and position
    demon->setName("DEMON_" + std::to_string(line) + "_" + std::to_string(collumn));
    demon->setGridPosition(line, collumn);
    
    // push demon in demon grid list
    std::vector<Demon*>::iterator demonIt;
    demonIt = std::find(_demonsInGridList.begin(), _demonsInGridList.end(), demon);
    if(demonIt == _demonsInGridList.end())
    {
        _demonsInGridList.push_back(demon);
    }
}

bool DisplayDemonsGrid::areDemonsAnimationsEnds()
{
    if(_demonsToMoveList.size() > 0)
    {
        return false;
    }
    
    _eventDispatcher->dispatchCustomEvent("DEMONS_ANIMATIONS_ENDS");
    
    return true;
}



