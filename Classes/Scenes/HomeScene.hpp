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
    
    CREATE_FUNC(HomeScene);
private:
    
};
#endif /* HomeScene_hpp */
