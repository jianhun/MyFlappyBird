//
//  GameScene.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-14.
//
//

#include "GameScene.h"
#include "GameGlobal.h"
#include "Utils.h"
#include "PopupResult.h"
#include "GameData.h"
#include "AudioController.h"
#include <cmath>
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/UtilsJNI.h"
#endif

#define Z_BG        0
#define Z_PIPE      1
#define Z_LAND      2
#define Z_BIRD      3
#define Z_SCORE     4
#define Z_STATETIP  4
#define Z_HELP      4
#define Z_RESULT    5

CCScene* GameScene::_scene = NULL;

CCScene* GameScene::scene(){
    _scene = CCScene::create();
    GameScene* layer = GameScene::create();
    _scene->addChild(layer);
    return _scene;
}

GameScene::GameScene():GameState(1), score(0), lastPressedItem(-1), newRecord(false), dieCount(0) {

}

GameScene::~GameScene(){
    if (pipesArray != NULL) {
        pipesArray->release();
        pipesArray = NULL;
    }
    
    if (buttonArray != NULL) {
        buttonArray->release();
        buttonArray = NULL;
    }
}

bool GameScene::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    //
    srand(time(0));
    AudioController::instance()->preLoadSfx("sfx_wing");
    AudioController::instance()->preLoadSfx("sfx_swooshing");
    AudioController::instance()->preLoadSfx("sfx_point");
    AudioController::instance()->preLoadSfx("sfx_hit");
    AudioController::instance()->preLoadSfx("sfx_die");
    //
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);    
    
    //bg
    bg = Utils::createSprite("bg_0");
    bg->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(bg, Z_BG);
    
    //land
    land = Utils::createSprite("land");
    land->setAnchorPoint(ccp(0.0, 0.0));
    land->setPosition(ccp(0.0, 0.0));
    this->addChild(land, Z_LAND);
        
    //bird
    bird = Bird::create();
    this->addChild(bird, Z_BIRD);
    
    //score
    scoreTip = CompnNumber::create();
    scoreTip->setCount(0, COMPNNUMBERMODE_BIG, 0);
    scoreTip->setAnchorPoint(ccp(0.5, 0.5));
    scoreTip->setPosition(ccpAdd(center,ccp(0, 150)));
    this->addChild(scoreTip, Z_SCORE);
    
    //stateTipReady
    stateTipReady = Utils::createSprite("text_ready");
    stateTipReady->setPosition(ccpAdd(center, ccp(0,60)));
    this->addChild(stateTipReady, Z_STATETIP);
            
    //help
    help = Utils::createSprite("tutorial");
    help->setPosition(ccpAdd(center, ccp(0, -20)));
    this->addChild(help, Z_HELP);
        
    //pipesArray
    pipesArray = CCArray::create();
    pipesArray->retain();
    
    //buttonsArray
    buttonArray = CCArray::create();
    buttonArray->retain();
    
    //touch events
    this->setTouchEnabled(true);
    
    //
    setStatus(GameReady);
    
    return true;
}

void GameScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    if (GameState == GameReady) {
        setStatus(GameRun);
        
        birdJump();
    }
    else if (GameState == GameRun) {
        birdJump();
        
    }
    else if (GameState == GameEnd) {

    }
    
    
    return true;
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCPoint pos = pTouch->getLocationInView();
    pos = CCDirector::sharedDirector()->convertToGL(pos);
    
    if (lastPressedItem >= 0 && lastPressedItem == Utils::buttonHitTest(pos, buttonArray)) {
        CompnButton *btn = (CompnButton*)buttonArray->objectAtIndex(lastPressedItem);
        btn->click();
        clickItem(btn->getBid());
    }
}

void GameScene::birdJump()
{
    bird->unscheduleUpdate();
    CCRotateTo *rotateUp = CCRotateTo::create(0.4, -20);
    CCRotateTo *rotateDown = CCRotateTo::create(0.7, 90);
    CCSequence *seq = CCSequence::create(CCEaseSineOut::create(rotateUp), CCEaseSineIn::create(rotateDown), NULL);
    bird->runAction(seq);
        
    bird->setMoveSpeed(ccp(0, 240));
    bird->setMoveAccSpeed(ccp(0, -600));
    bird->scheduleUpdate();
    
    this->scheduleOnce(schedule_selector(GameScene::playSfxWing), 0.1);
    //AudioController::instance()->playSfx("sfx_wing");
}

void GameScene::playSfxWing()
{
    AudioController::instance()->playSfx("sfx_wing");
}

void GameScene::birdFall(){
    float v = 300;
    float distance = bird->getPositionY() - (land->getContentSize().height + 10);
    float durMove = distance/v;
    CCMoveBy *moveBy = CCMoveBy::create(durMove, ccp(0, -distance));
    CCEaseSineIn *ease = CCEaseSineIn::create(moveBy);
    CCSequence *seq  = CCSequence::create(ease, CCCallFunc::create(this, callfunc_selector(GameScene::showResult)), NULL);
    bird->runAction(seq);
}

void GameScene::birdDie(bool dieReasonFall){
    bird->stopAllActions();
    bird->die();
    dieCount++;
    
    setStatus(GameEnd);
  
    if (dieReasonFall) {
        showResult();
        AudioController::instance()->playSfx("sfx_hit");
    }
    else {
        birdFall();
        AudioController::instance()->playSfx("sfx_die");
    }
    
}

void GameScene::showResult()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (dieCount >= 3) {
		JNI_showAdsScreen();
	}
#endif
    //show
    PopupResult *result = PopupResult::create(_scene, Z_RESULT, this, score, GameData::instance()->getHighScore(), newRecord);
    result->show();
}

void GameScene::setStatus(int state){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(screenSize.width * 0.5, screenSize.height * 0.5);
    
    GameState = state;
    if (state == GameReady) {
        
        //
        newRecord = false;
        //remove pipes if have
        for (int i = pipesArray->count()-1; i >= 0; i--) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            this->removeChild(pi);
        }
        pipesArray->removeAllObjects();
        
        //score
        score = 0;
        scoreTip->setCount(score);
        
        //show
        stateTipReady->setOpacity(255);
        help->setOpacity(255);
        
        //bg
        CCArray *bgAnimArray = Utils::createAnimArray("bg", 2);
        int bgRand = 0 + rand() % (1 - 0 + 1);
        bg->setDisplayFrame((CCSpriteFrame *)bgAnimArray->objectAtIndex(bgRand));
        
        //bird     
        CCMoveBy *birdMove = CCMoveBy::create(0.5, ccp(0, 10));
        CCRepeatForever *upDown = CCRepeatForever::create(CCSequence::create(birdMove, birdMove->reverse(), NULL));
        upDown->setTag(ActionTagBirdUpDown);
        bird->runAction(upDown);
        bird->setInit();
        bird->setPosition(ccpAdd(center, ccp(-60, 0)));
        bird->setRotation(0);

        //land
        CCAction *landMove = CCRepeatForever::create (CCSequence::create(CCMoveTo::create(48/SpeedLand, ccp(-48, 0)), CCMoveTo::create(0, ccp(0, 0)), NULL));
        landMove->setTag(ActionTagLandMove);
        land->runAction(landMove);
    }
    else if (state == GameRun) {
        //bird cancel upDown
        bird->stopActionByTag(ActionTagBirdUpDown);
        
        //tip and help fade action
        float durFade = 0.1;
        CCFadeOut *fade1 = CCFadeOut::create(durFade);
        CCFadeOut *fade2 = (CCFadeOut*)fade1->copy();
        stateTipReady->runAction(fade1);
        help->runAction(fade2);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
        this->unschedule(schedule_selector(GameScene::setPipes));
        this->schedule(schedule_selector(GameScene::setPipes), (screenSize.width/2 + 30)/SpeedPipe, kCCRepeatForever, 1);
    }
    else if (state == GameEnd) {
        this->unscheduleUpdate();
        this->unschedule(schedule_selector(GameScene::setPipes));
        //pipe action
        for (int i = 0 ; i < pipesArray->count(); i++) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            //pi->stopActionByTag(ActionTagPipeMove);
            pi->setMoveSpeed(ccp(0, 0));
        }
        
        //land action
        land->stopAllActions();
        
        //best score
        int highScore = GameData::instance()->getHighScore();
        if (score > highScore) {
            GameData::instance()->setHighScore(score);
            newRecord = true;
        }
    }
    
}

void GameScene::setPipes(){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //pipe
    Pipe *pipe1 = Pipe::create();
    this->addChild(pipe1, Z_PIPE);
    pipe1->setAnchorPoint(ccp(0.0, 0.0));
    pipe1->setPosition(ccp(screenSize.width, 0));
    pipesArray->addObject(pipe1);
    //action    
    pipe1->setMoveSpeed(ccp(-SpeedPipe, 0));
    pipe1->scheduleUpdate();
}

void GameScene::removePipes(CCNode *pipe){
    pipesArray->removeObject(pipe);
    this->removeChild(pipe);
}

void GameScene::update(float delta){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    if (GameState == GameRun && pipesArray != NULL && pipesArray->count() > 0) {
        //update score
        scoreTip->setCount(score);
        
        //rotate to 90
        if (bird->getRotation() >= 90) {
            bird->setRotateAccSpeed(0);
            bird->setRotateSpeed(0);
        }
        
        //hit land
        if (bird->getPositionY() <= land->getContentSize().height + 10) {
            birdDie(true);
            return;
        }
        
        //hit pipe
        for (int i = 0; i < pipesArray->count(); i++) {
            Pipe *pi = (Pipe*)pipesArray->objectAtIndex(i);
            
            //pipe should remove
            if (pi->getPositionX() < -(PipeWidth + screenSize.width)) {
                removePipes(pi);
                continue;
            }
            
            //score
            testPipePassed(pi);
            
            //hit
            if (testBird(pi)) {
                birdDie(false);
            }
        }
        
        
    }
}

bool GameScene::testBird(Pipe *pipe){
    //
    if (fabsf(bird->getPositionX() - (pipe->getPositionX() + PipeWidth/2)) < (PipeWidth + bird->getContentSize().width - 20)/2 ) {
        if (fabsf(bird->getPositionY() - pipe->getCenterH()) > pipe->getPipePadding() - bird->getContentSize().height/2 + 10) {
            AudioController::instance()->playSfx("sfx_hit");
            return true;
        }
    }
    return false;
}

void GameScene::testPipePassed(Pipe *pipe)
{
    if (!pipe->getPassed() && pipe->getPositionX() + PipeWidth/2 <= bird->getPositionX())
    {
        pipe->setPassed(true);
        score++;
        this->scheduleOnce(schedule_selector(GameScene::playSfxPoint), 0.1);
        //AudioController::instance()->playSfx("sfx_point");
    }
}

void GameScene::playSfxPoint()
{
    AudioController::instance()->playSfx("sfx_point");
}

void GameScene::clickItem(int bid){

}

bool GameScene::onPopupEventMenuCommand(cocos2d::CCLayer *component, const int menuId)
{
    menuCommand(menuId);
}

void GameScene::onPopupEventDismiss(CCLayer *component)
{
    
}

void GameScene::menuCommand(int menuId)
{
    if (menuId == KMenuRestart) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JNI_closeAdsScreen();
#endif
        setStatus(GameReady);
        AudioController::instance()->playSfx("sfx_swooshing");
    }
}




