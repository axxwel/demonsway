//
//  GameScene.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

#include "../DisplayObjects/DisplayScores.hpp"
#include "../DisplayObjects/DisplayGrid.hpp"
#include "../DisplayObjects/DisplayDemonsGrid.hpp"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
private:
    
    DisplayScores* _scoresDisplay = nullptr;
    
    DisplayGrid* _gridDisplay = nullptr;
    
    cocos2d::Sprite* _divingBoard = nullptr;
    
    DisplayDemonsGrid* _demonGridDisplay = nullptr;
    
    // return home callback
    void menuHomeCallback(cocos2d::Ref* pSender);
    
    // return home callback
    void menuGameCallback(cocos2d::Ref* pSender);
    
    // end game
    void gameOverStartCallback();
    void gameOverEndCallback();
};

#endif /* GameScene_hpp */
