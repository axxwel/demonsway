//
//  StaticGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 18/09/2020.
//

#ifndef StaticGrid_hpp
#define StaticGrid_hpp

#include "cocos2d.h"
class StaticGrid
{
public:
    /**
     * @brief Get the pixel position of grid case
     * @param LC line and collumn vector.
     * @param gridXY grid position in screen.
     * @return pixel position of grid case.
    */
    static cocos2d::Vec2 getPositionXY(const cocos2d::Vec2 LC);
    
private:
    /**
     *@brief Calculate the pixel position x an y of every grid case.
     *And push it in array (gridXY).
     *Array line and collumn contains the pixel position vector.
    */
    static bool initGrid();
    
};

//Global grid size variables
std::vector<std::vector<cocos2d::Vec2>> gridXY;
static const int GRID_SIZE = 6;
static const int GRID_SHIFT = 260;
static const int CASE_SIZE = 104;

#endif /* StaticGrid_hpp */
