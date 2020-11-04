//
//  StaticGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 18/09/2020.
//

#ifndef StaticGrid_hpp
#define StaticGrid_hpp

#include "cocos2d.h"

struct GridSize
{
    int width;
    int height;
};

class StaticGrid
{
public:
    /**
     * @brief Get the pixel position of grid case
     * @param LC line and collumn vector.
     * @return pixel position of grid case.
    */
    static cocos2d::Vec2 getPositionXY(const cocos2d::Vec2 LC);
    
    /**
     * @brief Get the grid size.
     * @return size of grid in pixel.
    */
    static GridSize getGridSize();
    
private:
    
    
    
};

//Global grid size variables
static const int GRID_NBR_CASE = 6;
static const int GRID_SHIFT = 260;
static const int CASE_SIZE = 104;
static const int GRID_BORDER_SIZE = 12;

#endif /* StaticGrid_hpp */
