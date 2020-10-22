//
//  DisplayDemonsGrid.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 12/10/2020.
//

#ifndef DisplayDemonsGrid_hpp
#define DisplayDemonsGrid_hpp

#include "cocos2d.h"

#include "../DisplayObjects/Demon.hpp"

class DisplayDemonsGrid : public cocos2d::Node
{
public:
    static DisplayDemonsGrid* create(cocos2d::Sprite* divingBoard);

    virtual bool init(cocos2d::Sprite* divingBoard);
    
    /**
     * @brief add new demon into the grid.
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
    
    int _actionTurn = 0;
    
    std::vector<Demon*> _demonsInGridList;
    
    std::vector<Demon*> _demonsActionList;
    
    std::vector<Demon*> _demonsToMoveList;
    
    // pointer to demon ready to jump in grid
    Demon* _demonDiver = nullptr;
    
    /**
     * @brief add new demon on the diving board
     * @return action type OK.
    */
    bool addNewDemonDiver();
    
    /**
     * @brief run all action in  grid.
     * @param turn number of times the function has been used.
    */
    void startActionGrid(int turn = 0);
    
    /**
     * @brief move demon in  grid.
     * @return a demon moved (true or false).
    */
    bool moveDemonsGrid();
    
    /**
     * @brief move demon in  grid.
     * @param demon  moving demon.
     * @return action type OK.
    */
    bool moveDemon(Demon* demon);
    
    /**
     * @brief add new demon in demon grid vector.
     * @param demon demon pointer will added into the grid.
     * @param l grid line.
     * @param c grid collumn
     * @return action type OK.
    */
    void setInGrid(Demon* demon, int l, int c);
    
    bool areDemonsAnimationsEnds();
};

#endif /* DisplayDemonsGrid_hpp */
