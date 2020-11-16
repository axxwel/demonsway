//
//  StaticSounds.hpp
//  cocos2d
//
//  Created by alexandre gimeno on 09/11/2020.
//

#ifndef StaticSounds_hpp
#define StaticSounds_hpp

#include "cocos2d.h"

class StaticSounds
{
public:
    
    /**
     * @brief play game music
     * @param theme music theme name.
    */
    static void playMusic(std::string theme);
    
    /**
     * @brief play game soud effect.
     * @param theme sound effect name.
    */
    static void playSound(std::string sound);
    
    /**
     * @brief preload all game sound.
    */
    static void preLoad();
    
private:
    
    
};


#endif /* StaticSounds_hpp */
