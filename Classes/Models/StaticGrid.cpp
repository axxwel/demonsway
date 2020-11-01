//
//  StaticGrid.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 18/09/2020.
//

#include "StaticGrid.hpp"

cocos2d::Vec2 StaticGrid::getPositionXY(const cocos2d::Vec2 LC)
{
    // get screen size
    auto director = cocos2d::Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    cocos2d::Vec2 origin = director->getVisibleOrigin();
    int gridPosX = visibleSize.width/2 + origin.x;
    int gridPosY = visibleSize.height/2 + origin.y;
    
    float y = LC.x * -CASE_SIZE + gridPosY + GRID_SHIFT;// + gridPosX - GRID_SHIFT;
    
    float x = LC.y * CASE_SIZE + gridPosX - GRID_SHIFT;// + gridPosY + GRID_SHIFT;
    
   
    // return position X and Y vector
    return cocos2d::Vec2(x, y);
}
