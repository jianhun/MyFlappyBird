//
//  AudioController.h
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#ifndef __testShao3__AudioController__
#define __testShao3__AudioController__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <string>

USING_NS_CC;
using namespace std;

class AudioController : public CCObject
{
public:
    AudioController();
    
    virtual ~AudioController();
    
    virtual bool init();
    
    static AudioController* instance();
    
    //bg
    void preLoadBgMusic(const char* clip);
    
    void playBgMusic(const char* clip, bool loop);
    
    void resumeBgMusic();
    
    void stopBgMusic();
    
    //sfx
    void preLoadSfx(const char* clip);
    
    void playSfx(const char* clip);
    
    void stopAllSfx();
private:
    static AudioController* _instance;
    
    CocosDenshion::SimpleAudioEngine* _engine;
    
};

#endif /* defined(__testShao3__AudioController__) */
