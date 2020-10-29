//
//  DisplayScores.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 28/10/2020.
//

#ifndef DisplayScores_hpp
#define DisplayScores_hpp

#include "cocos2d.h"

class DisplayScores : public cocos2d::Node
{
public:
    static DisplayScores* create();

    virtual bool init();
    
private:
    cocos2d::Node* scores = nullptr;
    
        
};

#endif /* DisplayScores_hpp */
