//
//  PopupResult.h
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#ifndef __testShao3__PopupResult__
#define __testShao3__PopupResult__

#include <iostream>
#include "cocos2d.h"
#include "CompnButton.h"
#include "CompnNumber.h"
#include "PopupEventDelegate.h"

USING_NS_CC;

class PopupResult : public CCLayer{
public:
    PopupResult(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int score, int bestScore, bool newRecord);
    
    ~PopupResult();
    
    virtual bool init();
    
    static PopupResult* create(CCScene *scene, const int zorder, PopupEventDelegate *delegate, int score, int bestScore, bool newRecord);
    
    void show();
    
    void schedualEntryEffect();
    
    void showScoreAnimation();
    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void clickItem(int bid);
    
    void dismiss();
private:
    CCSprite *_over;
    
    CCNode *_panel;
    CCSprite *_resultBg;
    CCSprite *_medal;
    CompnNumber *_cnScore;
    CompnNumber *_cnBestScore;
    CCSprite *_newRecord;
    
    CompnButton *reStart;
    CompnButton *record;
    
    int _score;
    int _bestScore;
    bool _isNewRecord;
    CCScene *_scene;
    int _zorder;
    PopupEventDelegate *_delegate;
    
    CCArray *_buttonArray;
    int _lastPressedItem;
    bool _enabled;
    int _entryEffectStep;
    int _scoreAnimationStep;
};

#endif /* defined(__testShao3__PopupResult__) */
