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
    jump,
    walk,
    removing,
    gameOver
};

enum DemonActionFunc {
    repeatAninForever,
    removeDemon
};

struct DemonPosition
{
    int line;
    int collumn;
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
    void action(DemonAction demonAction);
    
    /**
     * @brief set demon position on demon grid.
     * @param line grid position.
     * @param Collumn grid position.
    */
    void setDemonGridPosition(int line, int collumn);
    
    /**
     * @brief get demon position on grid.
     * @return DemonPosition line and collumn in demon grid.
    */
    DemonPosition getDemonGridPosition();
    
    /**
     * @brief get future demon position on grid after move.
     * @return DemonPosition line and collumn in demon grid.
    */
    DemonPosition getDemonGridWayPosition();
    
    /**
     * @brief display the score over the demon.
     * @param score value displayed.
    */
    void displayScore(int score);
    
    int getNameIndex();
    int getWayIndex();
    int getPositionIndex();
    
private:
    
    const float SCORE_MOVE_TIME = 0.5;
    
    // demon's type array
    const std::string NAME_ARRAY[9] = {"air","water","fire","forest","day","mecha","night","time","ground"};
    // demon's direction array
    const std::string WAY_ARRAY[4] = {"face","side","side","back"};
    // demon's color array
    const cocos2d::Color3B COLOR_ARRAY[9] = {cocos2d::Color3B::WHITE, cocos2d::Color3B::BLUE, cocos2d::Color3B::RED, cocos2d::Color3B::GREEN, cocos2d::Color3B(0,255,255), cocos2d::Color3B::GRAY, cocos2d::Color3B(127,71,221), cocos2d::Color3B::YELLOW, cocos2d::Color3B(166,124,82)};
    
    // demons init values
    int _nameIndex;
    int _wayIndex;
    
    // demons grid position value
    int _line;
    int _collumn;
    
    // demon sprite pointer
    cocos2d::Sprite* _demonSprite = nullptr;
    
    // action sprite pointer
    cocos2d::Action* _demonAction = nullptr;
    
    /**
     * @brief create demon frames array.
     * @param animName animation name.
     * @param count image animation amount.
     * @return animation frames vector.
    */
    cocos2d::Vector<cocos2d::SpriteFrame*> createAnimFrames(std::string animName, int count);
    
    /**
     * @brief set and start demon animation.
     * @param animFrames animation frames vector.
     * @param animFunc associate animation function.
     * @return action OK.
    */
    bool setAnimation(cocos2d::Vector<cocos2d::SpriteFrame*> animFrames, DemonActionFunc animFunc = repeatAninForever);
};

#endif /* Demon_hpp */
