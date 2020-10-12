//
//  DisplayDemonsGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 12/10/2020.
//

#ifndef DisplayDemonsGrid_hpp
#define DisplayDemonsGrid_hpp

#include "../DisplayObjects/Demon.hpp"

class DisplayDemonsGrid : public cocos2d::Node
{
public:
    static DisplayDemonsGrid* create(cocos2d::Sprite* divingBoard);

    virtual bool init(cocos2d::Sprite* divingBoard);
    
    /**
     * @brief add new demon in demon grid.
     * @param l grid line.
     * @param c grid collumn
     * @return action type OK.
    */
    bool addDemonGrid(int l, int c);
    
private:
    const float MOVE_TIME = 0.5;
    const float JUMP_SCALE = 1.5;
    const float DEMON_IN_GRID_SCALE = 0.8;
    
    cocos2d::Sprite* _divingBoard = nullptr;
    
    std::vector<Demon*> _demonsMovedList;
    
    std::vector<std::vector<Demon*>> _demonsGrid;
    
    // pointer to demon ready to jump in grid
    Demon* _demonDiver = nullptr;
    
    /**
     * @brief add new demon in demon grid.
     * @return action type OK.
    */
    bool addNewDemon();
};

#endif /* DisplayDemonsGrid_hpp */
