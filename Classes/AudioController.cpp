//
//  AudioController.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#include "AudioController.h"
#define KExtension ".mp3"

AudioController::AudioController():_engine(CocosDenshion::SimpleAudioEngine::sharedEngine())
{
    
}

AudioController::~AudioController()
{
    
}

bool AudioController::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!_engine);
        bRet = true;
    }while (0);
    
    return bRet;
}

AudioController* AudioController::_instance = NULL;
AudioController* AudioController::instance()
{
    if (_instance == NULL) {
        _instance = new AudioController();
        if (!_instance->init()) {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

void AudioController::preLoadBgMusic(const char *clip)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //char buffer[100];
    //sprintf(buffer, "music/%s%s", clip, KExtension);
    string name = "music/" + string(clip) + KExtension;
    _engine->preloadBackgroundMusic(name.c_str());
#endif
}

void AudioController::playBgMusic(const char *clip, bool loop)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    string music = string(clip) + KExtension;
    _engine->playBackgroundMusic(music.c_str(), loop);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(_engine->isBackgroundMusicPlaying()) {
        _engine->stopBackgroundMusic();
    }
    string musicName = "music/" + string(clip) + KExtension;
    _engine->preloadBackgroundMusic(musicName.c_str());
    _engine->playBackgroundMusic(musicName.c_str(), loop);
#endif

}

void AudioController::resumeBgMusic()
{
    _engine->resumeBackgroundMusic();
}

void AudioController::stopBgMusic()
{
    _engine->pauseBackgroundMusic();
}

void AudioController::preLoadSfx(const char *clip)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    string sfxName = "music/" + string(clip) + KExtension;
    _engine->preloadEffect(sfxName.c_str());
#endif
}

void AudioController::playSfx(const char *clip)
{ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    string music = string(clip) + KExtension;
    _engine->playEffect(music.c_str());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    string sfxName = "music/" + string(clip) + KExtension;
    _engine->playEffect(sfxName.c_str());
//    int soundID = _engine->playEffect(sfxName.c_str());
//    if(soundID != 0) {
//        _engine->resumeEffect(soundID);
//    }
#endif
}

void AudioController::stopAllSfx()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_engine->stopAllEffects();
#endif
}



