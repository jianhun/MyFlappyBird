//
//  GameData.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#include "GameData.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/UtilsJNI.h"
#endif

GameData::GameData()
{
};

GameData::~GameData()
{
};

static GameData* _instance = NULL;

GameData* GameData::instance()
{
    if (_instance == NULL) {
        _instance = new GameData();
        
        if (!_instance->init()) {
            CC_SAFE_DELETE(_instance);
        }
        
        if (!_instance->load()) {
            _instance->initData();
        }
        
    }
    return _instance;
}

bool GameData::init()
{
    return  true;
}

bool GameData::load()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCUserDefault* read = CCUserDefault::sharedUserDefault();
    _isExisted = read->getBoolForKey("IsExisted");
    if (!_isExisted) {
        return false;
    }
    _highScore = read->getIntegerForKey("HighScore");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _isExisted = JNI_getBool("IsExisted", false);
	if (!_isExisted) {
		return false;
	}
    _highScore = JNI_getInt("HighScore", 0);
#endif
    
    return true;
}

void GameData::initData()
{
    _isExisted = true;
    _highScore = 0;
    
    saveSettings();
}

void GameData::saveSettings()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCUserDefault* write = CCUserDefault::sharedUserDefault();
    write->setBoolForKey("IsExisted", _isExisted);
    write->setIntegerForKey("HighScore", _highScore);
    write->flush();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JNI_setBool("IsExisted", _isExisted);
    JNI_setInt("HighScore", _highScore);
#endif
}

void GameData::setHighScore(const int score)
{
    _highScore = score;
    saveSettings();
}

int GameData::getHighScore()
{
    return _highScore;
}




