//
//  GameScene.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

#include "../DisplayObjects/Demon.hpp"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
private:
    const float MOVE_TIME = 0.5;
    const float JUMP_SCALE = 1.5;
    const float DEMON_IN_GRID_SCALE = 0.8;
    
    cocos2d::Sprite* divingBoard = nullptr;
    
    // pointer to demon ready to jump in grid
    Demon* demonDiver = nullptr;
    
    /**
     * @brief add new demon in demon grid.
     * @return action type OK.
    */
    bool addNewDemon();
    
    /**
     * @brief add new demon in demon grid.
     * @param l grid line.
     * @param c grid collumn
     * @return action type OK.
    */
    bool addDemonGrid(int l, int c);
    
    // return home callback
    void menuHomeCallback(cocos2d::Ref* pSender);
};

#endif /* GameScene_hpp */
