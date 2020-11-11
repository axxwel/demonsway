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
    
    static void playMusic(std::string theme);
    
    static void playSound(std::string sound);
    
    static void preLoad();
    
private:
    
    static void backgroundMusicCallback(int audioID, std::string theme);
    
};

int _musicID = 0;
std::string _musicThemeStr = "void";


#endif /* StaticSounds_hpp */
