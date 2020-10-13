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
    dance,
    walk,
    removing
};

class Demon : public cocos2d::Node
{
public:
    static Demon* create();

    
    virtual bool init();
    
    /**
     * @brief send demon action.
     * @param DemonAction action type.
     * @return action type OK.
    */
    bool action(DemonAction demonAction);
    
    int getNameIndex();
    int getWayIndex();
    
private:
    
    // demon's type array
    const std::string NAME_ARRAY[9] = {"air","water","fire","forest","day","mecha","night","time","ground"};
    // demon's direction array
    const std::string WAY_ARRAY[4] = {"face","side","side","back"};
    
    // demons init values
    int _nameIndex;
    int _wayIndex;
    
    // demon sprite pointer
    cocos2d::Sprite* _demonSprite = nullptr;
    
    /**
     * @brief set and start demon animation.
     * @param animName animation name.
     * @param count image animation amount.
     * @return action OK.
    */
    bool setAnimation(std::string animName, int count);
};

#endif /* Demon_hpp */
