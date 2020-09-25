//
//  DemonsGrid.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#include "DemonsGrid.hpp"

DemonsGrid* DemonsGrid::create()
{
    //create new instance pointer
    DemonsGrid* ret = new (std::nothrow) DemonsGrid();
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

bool DemonsGrid::init()
{
    for(int l = 0; l < GRID_SIZE; l++)
    {
        for(int c = 0; c < GRID_SIZE; c++)
        {
            demonsGrid[l][c] = nullptr;
        }
    }
    
    return true;
}

bool DemonsGrid::newDemon(cocos2d::Vec2 LC)
{
    
    
    return true;
}

bool DemonsGrid::moveDemons()
{
    for(int l = 0; l < GRID_SIZE; l++)
    {
        for(int c = 0; c < GRID_SIZE; c++)
        {
            
        }
    }
    
    return true;
}
