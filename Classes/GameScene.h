//
//  GameScene.h
//  testShao3
//
//  Created by shaozhen on 14-2-14.
//
//

#ifndef __testShao3__GameScene__
#define __testShao3__GameScene__


#include "cocos2d.h"
#include "Pipe.h"
#include "CompnButton.h"
#include "CompnNumber.h"
#include "PopupEventDelegate.h"
#include "Bird.h"
USING_NS_CC;
using namespace std;

class GameScene : public CCLayer, public PopupEventDelegate {
public:
    GameScene();
    virtual ~GameScene();
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(GameScene);
    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void playSfxWing();
    
    void birdJump();
    
    void birdFall();
    
    void birdDie(bool dieReasonFall);
    
    void showResult();
    
    void setStatus(int state);
    
    void setPipes();
    
    void removePipes(CCNode *pipe);
    
    virtual void update(float delta);
    
    bool testBird(Pipe *pipe);
    
    void testPipePassed(Pipe *pipe);
    
    void playSfxPoint();
    
    void clickItem(int bid);
    
    virtual bool onPopupEventMenuCommand(CCLayer* component, const int menuId);
    
    virtual void onPopupEventDismiss(CCLayer* component);
    
    void menuCommand(int menuId);
    
protected:

private:
    static CCScene *_scene;
    
    CCSprite *bg;
    CCSprite *land;
    Bird *bird;
    CCArray *pipesArray;
    CompnNumber *scoreTip;
    CCSprite *stateTipReady;
    CCSprite *help;
    CCArray *buttonArray;
    
    int GameState;
    int score;
    int lastPressedItem;
    bool newRecord;
    int dieCount;
};

#endif /* defined(__testShao3__GameScene__) */
