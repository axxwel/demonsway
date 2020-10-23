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
    
    // create grid array if null (frist call)
    if(gridXY.size() <= 0)
        initGrid();
    
    // return position X and Y vector
    return cocos2d::Vec2(gridXY[LC.x][LC.y].x + gridPosX,
    gridXY[LC.x][LC.y].y + gridPosY);
}

bool StaticGrid::initGrid()
{
    // clean grid array if first call
    gridXY.clear();
    
    // fill array where every case content pixel position vector.
    for (int l = 0; l <= GRID_SIZE; l++) {
       
        float y = l * -CASE_SIZE + GRID_SHIFT;
        std::vector<cocos2d::Vec2> line;
        
        for (int c = 0; c <= GRID_SIZE; c++) {
            
            float x = c * CASE_SIZE - GRID_SHIFT;
            cocos2d::Vec2 positionXY = {x,y};
            line.push_back(positionXY);
        }
        
        gridXY.push_back(line);
    }
    
    return true;
}
