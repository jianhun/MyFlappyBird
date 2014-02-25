//
//  SplashScene.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-25.
//
//

#include "SplashScene.h"
#include "GameScene.h"

SplashScene::SplashScene(CCScene *scene):_scene(scene)
{
    
}

SplashScene::~SplashScene()
{
    
}

SplashScene* SplashScene::create(cocos2d::CCScene *scene)
{
    SplashScene* spl = new SplashScene(scene);
    if (spl && spl->init()) {
        spl->autorelease();
        return spl;
    }
    else {
        CC_SAFE_DELETE(spl);
        return NULL;
    }
}

CCScene* SplashScene::scene()
{
    CCScene *scene = CCScene::create();
    
    SplashScene *layer = SplashScene::create(scene);
    
    
    scene->addChild(layer);
    
    return scene;
}

bool SplashScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5); 
    
    CCLayerColor *color = CCLayerColor::create(ccc4(255, 255, 255, 255));
    this->addChild(color);
    
    _logo = CCSprite::create("360logo.png");
    this->addChild(_logo);
    _logo->setPosition(center);
    
    return true;
}

void SplashScene::onExit()
{
    CCTextureCache::sharedTextureCache()->removeTextureForKey("360logo.png");
    
    //super onExit
    CCLayer::onExit();
}

void SplashScene::onEnterTransitionDidFinish()
{
    //super
    CCLayer::onEnterTransitionDidFinish();
    
    CCFadeOut *fade = CCFadeOut::create(1);
    CCSequence *seq = CCSequence::create(CCDelayTime::create(0.8), fade, CCCallFunc::create(this, callfunc_selector(SplashScene::gotoScene)), NULL);
    _logo->runAction(seq);
}

void SplashScene::gotoScene()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1, GameScene::scene()));
}


