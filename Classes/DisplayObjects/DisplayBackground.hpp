//
//  DisplayBackground.hpp
//  demonsway
//
//  Created by alexandre gimeno on 16/09/2020.
//

#ifndef DisplayBackground_hpp
#define DisplayBackground_hpp

#include "cocos2d.h"

class DisplayBackground : public cocos2d::Node
{
public:
    static DisplayBackground* create();

    virtual bool init();
    
private:
    cocos2d::Node* background = nullptr;
    
    /**
     * @brief create and start background animation.
    */
    void moveBackground();
};

#endif /* DisplayBackground_hpp */
