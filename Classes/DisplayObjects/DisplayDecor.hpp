//
//  DisplayDecor.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 07/11/2020.
//

#ifndef DisplayDecor_hpp
#define DisplayDecor_hpp

#include "cocos2d.h"

class DisplayDecor : public cocos2d::Node
{
public:
    static DisplayDecor* create();

    virtual bool init();
    
    void addTitle();
    
    void addScores(int score, int combo);
    
private:
    cocos2d::Node* _decor = nullptr;
    
    /**
     * @brief create and start decor animation.
    */
    void moveDecor();
};

#endif /* DisplayDecor_hpp */
