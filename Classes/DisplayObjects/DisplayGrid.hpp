//
//  DisplayGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 18/09/2020.
//

#ifndef DisplayGrid_hpp
#define DisplayGrid_hpp

#include "cocos2d.h"
#include "../Models/StaticGrid.hpp"

class DisplayGrid : public cocos2d::Node
{
public:
    static DisplayGrid* create();

    virtual bool init();
    
private:
    
    static const int GRID_SHIFT = 260;
    static const int BTN_SHIFT_HEIGHT = 24;
    
    int cornerGridArray [GRID_SIZE + 1][GRID_SIZE + 1];
    int gridArray [GRID_SIZE][GRID_SIZE] = {{1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1},
                                            {1,1,1,1,1,1}};
    
    /**
     * @brief Get the corner image code position.
     * @param pSender button grid reference.
     * @param line button touch line number.
     * @param collumn button touch collumn number.
    */
    void gridButtonCallback(cocos2d::Ref* pSender, int line, int collumn);
    
    /**
     * @brief Get the corner image code position.
     * @param line gridArray line.
     * @param collumn gridArray collumn.
     * @return code position std::string.
    */
    std::string cornerName(int line, int collumn);
};

#endif /* DisplayGrid_hpp */
