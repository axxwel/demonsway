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
    std::string themeStr = "demon_way_" + theme + "_theme.mp3";
    
    if(themeStr != _musicThemeStr)
    {
        _musicThemeStr = themeStr;
        
        if(_musicThemeStr == "demon_way_home_theme.mp3")
        {
            if(AudioEngine::getState(_musicID) == AudioEngine::AudioState::PLAYING)
            {
                AudioEngine::stop(_musicID);
            }
            
            _musicID = AudioEngine::play2d(_musicThemeStr, true, 0.4f);
        }
        else
        {
            AudioEngine::setLoop(_musicID, false);
            AudioEngine::setFinishCallback(_musicID, StaticSounds::backgroundMusicCallback);
        }
    }
}

void StaticSounds::backgroundMusicCallback(int audioID, std::string theme)
{
    AudioEngine::stop(_musicID);
    _musicID = AudioEngine::play2d(_musicThemeStr, true, 0.4f);
}

void StaticSounds::playSound(std::string sound)
{
    std::string soundStr = sound + ".mp3";
    
    AudioEngine::play2d(soundStr, false, 1.0f);
}

void StaticSounds::preLoad()
{
    std::vector<std::string> soundsMap = {
        "aplause", "button", "coin_triple", "coin", "demon_explose", "demon_jump", "demon_walk", "game_over", "window"
    };
    
    std::vector<std::string>::iterator soundIt;
    for(soundIt = soundsMap.begin(); soundIt != soundsMap.end(); soundIt++)
    {
        std::string sound = *soundIt + ".mp3";
        AudioEngine::preload(sound);
    }
}
