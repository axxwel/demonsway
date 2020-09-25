//
//  GameScene.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

#include "../DisplayObjects/DisplayGrid.hpp"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
private:
    
    const int MOVE_TIME = 1;
    
    void menuHomeCallback(cocos2d::Ref* pSender);
};

#endif /* GameScene_hpp */