//
//  Bird.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#include "Bird.h"
#include "Utils.h"

Bird::~Bird()
{
    if (_birdFrams != NULL) {
        _birdFrams->release();
        _birdFrams = NULL;
    }
}

bool Bird::init()
{
    if (!AniNode::init()) {
        return false;
    }
    
    _birdFrams = CCArray::create();
    _birdFrams->retain();
    
    char *arr[] = {"bird0", "bird1", "bird2"};
    for (int i = 0; i < 3; i++) {       
        CCArray *birdAnimArray = Utils::createAnimArray(arr[i], 3);
        _birdFrams->addObject(birdAnimArray);
    }
    
    _bird = Utils::createSprite("bird0_1");
    this->addChild(_bird);
    this->setContentSize(_bird->getContentSize());
    
    return true;
}

void Bird::setInit()
{
    int birdRand =  0 + rand() % (2 - 0 + 1);
    CCArray *birdAnimArray = (CCArray*)_birdFrams->objectAtIndex(birdRand);
    CCAnimation *birdAnimation = CCAnimation::createWithSpriteFrames(birdAnimArray, 0.1f);
    CCAnimate *birdAnimate = CCAnimate::create(birdAnimation);
    _bird->runAction(CCRepeatForever::create(birdAnimate));
    
    setMoveAccSpeed(ccp(0, 0));
    setMoveSpeed(ccp(0, 0));
    setRotateAccSpeed(0);
    setRotateSpeed(0);

}

void Bird::die()
{
    _bird->stopAllActions();
    setMoveAccSpeed(ccp(0, 0));
    setMoveSpeed(ccp(0, 0));
    setRotateAccSpeed(0);
    setRotateSpeed(0);
}