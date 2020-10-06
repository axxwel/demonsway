//
//  Demon.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 23/09/2020.
//

#ifndef Demon_hpp
#define Demon_hpp

#include "cocos2d.h"

enum DemonAction {
    enterDiving,
    waiting,
    blink,
    dance,
    walk
};

class Demon : public cocos2d::Node
{
public:
    static Demon* create();

    virtual bool init();
    
    bool action(DemonAction demonAction);
    
private:
    const std::string NAME_ARRAY[9] = {"Air","Water","Fire","Forest","Day","Mecha","Night","Time","Ground"};
    const std::string WAY_ARRAY[4] = {"face","side","side","back"};
    
    int nameIndex;
    int wayIndex;
    
    std::string nameStr;
    std::string wayStr;
    
    cocos2d::Sprite* demonSprite = nullptr;
    
    bool setAnimation(std::string format, int count);
};

#endif /* Demon_hpp */
