//
//  DemonsGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#ifndef DemonsGrid_hpp
#define DemonsGrid_hpp

#include "cocos2d.h"

#include "../Models/StaticGrid.hpp"

#include "../DisplayObjects/Demon.hpp"


class DemonsGrid : public cocos2d::Node
{
public:
    static DemonsGrid* create();

    virtual bool init();
    
    bool newDemon(cocos2d::Vec2 LC);
    
private:
    
    Demon* demonsGrid[GRID_SIZE - 1][GRID_SIZE - 1];
    
    bool moveDemons();
    
};

#endif /* DemonsGrid_hpp */
