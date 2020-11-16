//
//  StaticSounds.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 09/11/2020.
//

#include "StaticSounds.hpp"

#include "audio/include/AudioEngine.h"

USING_NS_CC;

void StaticSounds::playMusic(std::string theme)
{
    //PLAY GAME MUSIC
}

void StaticSounds::playSound(std::string sound)
{
    // format sound file name
    std::string soundStr = sound + ".mp3";
    
    // play sound (file name, repeat, volume)
    AudioEngine::play2d(soundStr, false, 1.0f);
}

void StaticSounds::preLoad()
{
    // create sounds list name
    std::vector<std::string> soundsList = {
        "aplause", "button", "coin_triple", "coin", "demon_explose", "demon_jump", "demon_walk", "game_over", "window"
    };
    
    // load all game sounds
    std::vector<std::string>::iterator soundIt;
    for(soundIt = soundsList.begin(); soundIt != soundsList.end(); soundIt++)
    {
        std::string sound = *soundIt + ".mp3";
        AudioEngine::preload(sound);
    }
}
