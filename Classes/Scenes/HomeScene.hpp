//
//  HomeScene.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 15/09/2020.
//

#ifndef HomeScene_hpp
#define HomeScene_hpp

#include "cocos2d.h"

class HomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // buttons callback
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuScoresCallback(cocos2d::Ref* pSender);
    
    void menuSoundCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HomeScene);
private:
    
};
#endif /* HomeScene_hpp */
