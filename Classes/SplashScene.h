//
//  SplashScene.h
//  testShao3
//
//  Created by shaozhen on 14-2-25.
//
//

#ifndef __testShao3__SplashScene__
#define __testShao3__SplashScene__

#include "cocos2d.h"
USING_NS_CC;

class SplashScene : public CCLayer
{
public:
    virtual bool init();
    
    static CCScene* scene();
    
    SplashScene(CCScene *scene);
    
    ~SplashScene();
    
    static SplashScene* create(CCScene *scene);
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExit();
private:
    //func
    void gotoScene();
    
    //vars
    CCScene *_scene;
    
    CCSprite *_logo;
    
    
    
    


};


#endif /* defined(__testShao3__SplashScene__) */
