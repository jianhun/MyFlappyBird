#include "AppDelegate.h"
#include "GameScene.h"
#include "SplashScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    // Multi-Resolution support
    CCSize frameSize = pEGLView->getFrameSize();
    CCSize lsSize = CCSizeMake(288, 512);
    float scaleX = (float) frameSize.width/lsSize.width;
    float scaleY = (float) frameSize.height/lsSize.height;
    float scale = 0.0f;
    if (scaleX > scaleY) {
        scale = scaleX/(frameSize.height/(float)lsSize.height);
    }
    else{
        scale = scaleY/(frameSize.width/(float)lsSize.width);
    }
    
    
    pEGLView->setDesignResolutionSize(lsSize.width , lsSize.height , kResolutionNoBorder);
    	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();
    //CCScene *pScene = SplashScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
