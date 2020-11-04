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
    
    void addToCombo(int combo);
    
    void setScore();
    
private:
    const float COMBO_MOVE_TIME = 0.5;
    
    cocos2d::Node* scores = nullptr;
    
    cocos2d::Label* _labelScore;
    cocos2d::Label* _labelCombo;
    
    int _score = 0;
    int _combo = 0;
};

#endif /* DisplayScores_hpp */
