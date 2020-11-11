//
//  DisplayScores.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 28/10/2020.
//

#ifndef DisplayScores_hpp
#define DisplayScores_hpp

#include "cocos2d.h"

struct ScoresNumber
{
    int score;
    int combo;
};

class DisplayScores : public cocos2d::Node
{
public:
    static DisplayScores* create();

    virtual bool init();
    
    /**
     * @brief add score demon moved or removed to combo.
     * @param combo  number added (1 move or 3 remove).
    */
    void addToCombo(int combo);
    
    /**
     * @brief at turn end, add combo number to game score .
    */
    void setScore();
    
    /**
     * @brief at turn end, add combo number to game score .
     * @return scores
    */
    ScoresNumber getScore();
    
private:
    const float COMBO_MOVE_TIME = 0.5;
    
    cocos2d::Node* scores = nullptr;
    
    cocos2d::Label* _labelScore;
    cocos2d::Label* _labelCombo;
    
    int _score = 0;
    int _combo = 0;
    int _bestCombo = 0;
};

#endif /* DisplayScores_hpp */
